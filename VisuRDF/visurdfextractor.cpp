#include "visurdfextractor.h"

GrapheRDF VisuRDFExtractor::grapheRDF ;

string VisuRDFExtractor::baseURI = "";

ObjetRDF VisuRDFExtractor::objetRDF;// objet RDF en cours d extraction

RelationRDF VisuRDFExtractor::relationRDF;

VisuRDFExtractor::VisuRDFExtractor()
{
}




/* rdfprint.c: print triples from parsing RDF/XML */

//gcc -o rdfprint rdfprint.c `pkg-config raptor2 --cflags --libs`


vector<string> VisuRDFExtractor::split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}



void VisuRDFExtractor::printVector(string str){

    vector<string> sep = split(str, '/');

    // If using C++11 (which I recommend)
    /* for(string t : sep)
   *  cout << t << endl;
   */

    for(int i = 0; i < sep.size(); ++i)
        cout << sep[i] << endl;

}

QName* VisuRDFExtractor::getSubject( raptor_statement* triple){

    if(triple->subject) {
        if(triple->subject->type == RAPTOR_TERM_TYPE_BLANK){
            string str( (const char*)triple->subject->value.blank.string);

            return new QName  (str);
        }else{
            string str( (const char*)raptor_uri_as_string(triple->subject->value.uri));
            return new QName  (str);
        }
    }
    return NULL;
}
QName* VisuRDFExtractor::getObbject( raptor_statement* triple){
    if(triple->object) {
        string datatype;
        if(triple->object->type == RAPTOR_TERM_TYPE_LITERAL) {
            if(triple->object->value.literal.datatype) {
                raptor_uri* dt_uri = triple->object->value.literal.datatype;
                datatype = string( (const char*)raptor_uri_as_string(dt_uri));

            }

            string str( (const char*)triple->object->value.literal.string);

            QName *qname = new QName  (str);
            qname->setDatatype(datatype);
           // printf("object str1: %s\n",qname->toString().c_str());
            return qname;


        } else if(triple->object->type == RAPTOR_TERM_TYPE_BLANK){
            string str( (const char*)triple->object->value.blank.string);
            return new QName  (str);
        } else {

            string str( (const char*)raptor_uri_as_string(triple->object->value.uri));
            return new QName  (str);

        }
    }

    return 0;

}
QName* VisuRDFExtractor::getPredicate( raptor_statement* triple){

    if(triple->predicate){

        string predicate ( (const char*)raptor_uri_as_string(triple->predicate->value.uri));
        return new QName  (predicate);

    }
    return 0;

}

void VisuRDFExtractor::print_object(ObjetRDF _objetRDF){

    for (ObjetRDF::const_iterator iter = _objetRDF.begin(); iter != _objetRDF.end(); iter++)
    {
        typedef list<string>::const_iterator ListIterator;
        for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
            cout << "\t\t"<<  iter->first << " : " << *list_iter << endl;

    }
    cout <<  endl;


}

void VisuRDFExtractor::print_map(){
    cout << "Impression des objets du graphe" <<endl;
    for (GrapheRDF::const_iterator grapheiter = grapheRDF.begin(); grapheiter != grapheRDF.end(); grapheiter++)
    {
        cout << grapheiter->first << " : " <<endl;
        typedef list<ObjetRDF>::const_iterator ListObjetRDFIterator;
        list < ObjetRDF > listOfRDFObject = grapheiter->second;
        for (ListObjetRDFIterator iter = listOfRDFObject.begin(); iter != listOfRDFObject.end(); iter++)
        {
            print_object(*iter);

        }
    }


}

 void VisuRDFExtractor::print_relations(){
     cout << "Impression des relations du graphe" <<endl;
     for (RelationRDF::const_iterator iter = relationRDF.begin(); iter != relationRDF.end(); iter++)
     {
         cout << iter->first << ":" <<endl;
         typedef list<string>::const_iterator ListIterator;
         for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
             cout << "\t\t"<< *list_iter << endl;

     }
     cout <<  endl;

 }

void VisuRDFExtractor::handle_triple(void* user_data, raptor_statement* triple)
{

    if(triple->predicate){
        QName* predicate = getPredicate(triple);
        if(predicate->getName().compare("type") == 0){//un nouvel objet vient d etre detecte
            if(objetRDF.size() !=0 ){
                list<string> listOfType = objetRDF["type"];
                list < ObjetRDF > listOfInstance = grapheRDF[listOfType.front()];
                listOfInstance.push_back( objetRDF);
                grapheRDF[listOfType.front()] = listOfInstance;
                objetRDF.clear();

            }
            //printf("predicate qname  : %s\n", predicate->toString().c_str());
            QName* subject = getSubject(triple);
            list<string> listOfprop;
            listOfprop.push_back(subject->getName());
            objetRDF["name"] = listOfprop;


            //printf("subject qname  : %s\n", subject->toString().c_str());
            QName* object = getObbject(triple);
            list<string> listOfprop1;
            listOfprop1.push_back(object->getName());
            objetRDF["type"] = listOfprop1;
            //printf("object qname  : %s\n", object->toString().c_str());

        }else{// c est soit une propriete simple soit une resource
            QName* object = getObbject(triple);
            if(object->getBaseUri().compare(baseURI) == 0){// cest une association

                list<string> listOfName = objetRDF["name"];
                list < string > listOfRel = relationRDF[listOfName.front()];
                listOfRel.push_back(object->getName());
                relationRDF[listOfName.front()] = listOfRel;


            }
            list<string> listOfprop = objetRDF[predicate->getName()];
            listOfprop.push_back( object->getName());
            objetRDF[predicate->getName()] = listOfprop;
        }
    }


    return;
}
void VisuRDFExtractor::parse_rdf_triple(char *rdfFile)
{
    raptor_world *world = NULL;
    raptor_parser* rdf_parser = NULL;
    unsigned char *uri_string;
    raptor_uri *uri, *base_uri;

    world = raptor_new_world();

    rdf_parser = raptor_new_parser(world, "rdfxml");



    raptor_parser_set_statement_handler(rdf_parser, NULL, handle_triple);

    uri_string = raptor_uri_filename_to_uri_string(rdfFile);
    uri = raptor_new_uri(world, uri_string);
    base_uri = raptor_uri_copy(uri);

    string str ((const char*)raptor_uri_as_string(base_uri));
    size_t size = str.find_last_of("/");
    baseURI = str.substr(0,size+1);


    raptor_parser_parse_file(rdf_parser, uri, base_uri);

    raptor_free_parser(rdf_parser);

    raptor_free_uri(base_uri);
    raptor_free_uri(uri);
    raptor_free_memory(uri_string);

    raptor_free_world(world);

    return ;
}
