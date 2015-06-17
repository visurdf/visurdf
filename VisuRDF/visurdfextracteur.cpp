#include "visurdfextracteur.h"

GrapheRDF VisuRDFExtracteur::grapheRDF ;
string VisuRDFExtracteur::uriDeBase = "";

// objet RDF en cours d extraction
ObjetRDF VisuRDFExtracteur::objetRDF;
RelationRDF VisuRDFExtracteur::relationRDF;

VisuRDFExtracteur::VisuRDFExtracteur() {

}

/* rdfprint.c: print triples from parsing RDF/XML */

//gcc -o rdfprint rdfprint.c `pkg-config raptor2 --cflags --libs`


/**
 * @brief VisuRDFExtracteur::split
 * @param str
 * @param delimiteur
 * @return vector<string>
 */

vector<string> VisuRDFExtracteur::split(string str, char delimiteur) {

    vector<string> internal;
    // change le string en un stream
    stringstream ss(str);
    string tok;

    while(getline(ss, tok, delimiteur)) {
        internal.push_back(tok);
    }

    return internal;
}


/**
 * @brief VisuRDFExtracteur::afficherVecteur
 * @param str
 */

void VisuRDFExtracteur::afficherVecteur(string str) {

    vector<string> separateur = split(str, '/');

    // If using C++11 (which I recommend)
    /* for(string t : sep)
   *  cout << t << endl;
   */

    for(int i = 0; i < separateur.size(); ++i)
        cout << separateur[i] << endl;
}


/**
 * @brief VisuRDFExtracteur::getSubject
 * @param triple
 * @return
 */

QName* VisuRDFExtracteur::getSujet(raptor_statement* triple) {

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


/**
 * @brief VisuRDFExtracteur::getObjet
 * @param triple
 * @return
 */

QName* VisuRDFExtracteur::getObjet( raptor_statement* triple) {

    if(triple->object) {

        string typeDeDonnee;
        if(triple->object->type == RAPTOR_TERM_TYPE_LITERAL) {

            if(triple->object->value.literal.datatype) {
                raptor_uri* dtUri = triple->object->value.literal.datatype;
                typeDeDonnee = string((const char*)raptor_uri_as_string(dtUri));
            }

            string str( (const char*)triple->object->value.literal.string);
            QName *qname = new QName  (str);
            qname->setTypeDeDonnee(typeDeDonnee);
           // printf("object str1: %s\n",qname->toString().c_str());
            return qname;

        } else if(triple->object->type == RAPTOR_TERM_TYPE_BLANK) {
            string str((const char*)triple->object->value.blank.string);
            return new QName  (str);

        } else {
            string str((const char*)raptor_uri_as_string(triple->object->value.uri));
            return new QName (str);
        }
    }

    return 0;
}


/**
 * @brief VisuRDFExtracteur::getPredicat
 * @param triple
 * @return
 */

QName* VisuRDFExtracteur::getPredicat(raptor_statement* triple) {

    if(triple->predicate) {
        string predicate ((const char*)raptor_uri_as_string(triple->predicate->value.uri));
        return new QName (predicate);
    }

    return 0;
}


/**
 * @brief VisuRDFExtracteur::afficherObjet
 * @param _objetRDF
 */

void VisuRDFExtracteur::afficherObjet(ObjetRDF _objetRDF) {

    for (ObjetRDF::const_iterator iter = _objetRDF.begin(); iter != _objetRDF.end(); iter++) {
        typedef list<string>::const_iterator ListIterator;
        for (ListIterator listIter = iter->second.begin(); listIter != iter->second.end(); listIter++)
            cout << "\t\t"<<  iter->first << " : " << *listIter << endl;
    }
    cout <<  endl;
}


/**
 * @brief VisuRDFExtracteur::afficherMap
 */

void VisuRDFExtracteur::afficherMap() {

    cout << "Impression des objets du graphe" <<endl;
    for (GrapheRDF::const_iterator grapheIter = grapheRDF.begin(); grapheIter != grapheRDF.end(); grapheIter++) {
        cout << grapheIter->first << " : " <<endl;
        typedef list<ObjetRDF>::const_iterator ListObjetRDFIterator;
        list <ObjetRDF> listObjetsRDF = grapheIter->second;

        for (ListObjetRDFIterator iter = listObjetsRDF.begin(); iter != listObjetsRDF.end(); iter++) {
            afficherObjet(*iter);
        }
    }
}


/**
  * @brief VisuRDFExtracteur::afficherRelations
  */

void VisuRDFExtracteur::afficherRelations() {

    cout << "Impression des relations du graphe" <<endl;
    for (RelationRDF::const_iterator iter = relationRDF.begin(); iter != relationRDF.end(); iter++)
    {
        cout << iter->first << ":" <<endl;
        typedef list<string>::const_iterator ListIterator;

        for (ListIterator listIter = iter->second.begin(); listIter != iter->second.end(); listIter++)
            cout << "\t\t"<< *listIter << endl;
    }
    cout <<  endl;
}


/**
 * @brief VisuRDFExtracteur::gestionnaireDeTriplets
 * @param donnee_utilisateur
 * @param triple
 */

// le parametre donnee_utilisateur (ex user_data) n'est pas utilisé ?
void VisuRDFExtracteur::gestionnaireDeTriplets(void* donnee_utilisateur, raptor_statement* triple) {

    if(triple->predicate) {
        QName* predicat = getPredicat(triple);

        //un nouvel objet vient d etre detecte
        if(predicat->getNom().compare("type") == 0) {
            if(objetRDF.size() !=0 ) {
                list<string> listeDesTypes = objetRDF["type"];
                list <ObjetRDF> listeDesInstances = grapheRDF[listeDesTypes.front()];
                listeDesInstances.push_back( objetRDF);
                grapheRDF[listeDesTypes.front()] = listeDesInstances;
                objetRDF.clear();
            }

            //printf("predicate qname  : %s\n", predicate->toString().c_str());
            QName* sujet = getSujet(triple);
            list<string> listeDeProprietes;
            listeDeProprietes.push_back(sujet->getNom());
            objetRDF["name"] = listeDeProprietes;

            //printf("subject qname  : %s\n", subject->toString().c_str());
            QName* objet = getObjet(triple);
            list<string> listeDeProprietes1;
            listeDeProprietes1.push_back(objet->getNom());
            objetRDF["type"] = listeDeProprietes1;
            //printf("object qname  : %s\n", object->toString().c_str());

        } else {
        // c'est soit une propriete simple soit une ressource
            QName* objet = getObjet(triple);
            if(objet->getUriDeBase().find(uriDeBase) == 0){// cest une association
                list<string> listeDeNoms = objetRDF["name"];
                list < string > listeDeRelations = relationRDF[listeDeNoms.front()];
                listeDeRelations.push_back(objet->getNom());
                relationRDF[listeDeNoms.front()] = listeDeRelations;

            } else {
                /* list<string> listeDeProprietes2 = objetRDF[predicat->getNom()];
                listeDeProprietes2.push_back(objet->getNom());
                objetRDF[predicat->getNom()] = listeDeProprietes2;
*/

                size_t pos = predicat->getNom().find_last_of(".");
                string val  = predicat->getNom().substr(pos+1, predicat->getNom().size());

                list<string> listeDeProprietes2 = objetRDF[val];


                listeDeProprietes2.push_back(objet->getNom());

                objetRDF[val] = listeDeProprietes2;

            }
        }
    }

    return;
}


/**
 * @brief VisuRDFExtracteur::parserTripletRdf
 * @param fichierRdf
 */

void VisuRDFExtracteur::parserTripletRdf(const char *fichierRdf) {

    raptor_world* world = NULL;
    raptor_parser* parserRdf = NULL;
    unsigned char* stringUri;
    raptor_uri *uri, *uriDeBase1;

    world = raptor_new_world();

    parserRdf = raptor_new_parser(world, "rdfxml");

    raptor_parser_set_statement_handler(parserRdf, NULL, gestionnaireDeTriplets);

    stringUri = (unsigned char*)fichierRdf;//raptor_uri_filename_to_uri_string(fichierRdf);    
    uri = raptor_new_uri(world, stringUri);
    uriDeBase1 = raptor_uri_copy(uri);

    string str ((const char*)raptor_uri_as_string(uriDeBase1));
    size_t size = str.find_last_of("/");
    uriDeBase = str.substr(0,size+1);

    raptor_parser_parse_file(parserRdf, uri, uriDeBase1);

    list<string> listeDesTypes = objetRDF["type"];
    list <ObjetRDF> listeDesInstances = grapheRDF[listeDesTypes.front()];
    listeDesInstances.push_back( objetRDF);
    grapheRDF[listeDesTypes.front()] = listeDesInstances;
    objetRDF.clear();

    raptor_free_parser(parserRdf);

    raptor_free_uri(uriDeBase1);
    raptor_free_uri(uri);
    //raptor_free_memory(stringUri);

    raptor_free_world(world);

    return;
}


/**
  * @brief VisuRDFExtracteur::getClasses
  * @return
  */

 set<string> VisuRDFExtracteur::getClasses(){

    set<string> listeDesClasses = set<string>();

    for (GrapheRDF::const_iterator grapheIter = grapheRDF.begin(); grapheIter != grapheRDF.end(); grapheIter++)

        listeDesClasses.insert(grapheIter->first);

    return listeDesClasses;
 }

 void VisuRDFExtracteur::clearModule(){

     VisuRDFExtracteur::objetRDF.clear();
     VisuRDFExtracteur::uriDeBase = "";
     VisuRDFExtracteur::grapheRDF.clear();
     VisuRDFExtracteur::relationRDF.clear();

 }
 /*
 set< string > VisuRDFExtracteur::getProperties(string clazz){
     list< ObjetRDF > listOfObjetRDF = grapheRDF[clazz];
     // recuperation de la liste des proprietes y compris celles qui n'ont pas de valeurs significatives
     ObjetRDF objetRDF  = *listOfObjetRDF.begin();
     set< string > listOfProperties = set< string >();
     for (ObjetRDF::const_iterator objetRDFiter = objetRDF.begin(); objetRDFiter != objetRDF.end(); objetRDFiter++)
         listOfProperties.insert(objetRDFiter->first);

     //filtrage des proprietes sans valeur significative
     bool isEmpty = false;
     for (ObjetRDF::const_iterator iter = _objetRDF.begin(); iter != _objetRDF.end(); iter++)
     {

         for (ObjetRDF::const_iterator objetRDFiter = objetRDF.begin(); objetRDFiter != objetRDF.end(); objetRDFiter++)
             listOfProperties.insert(objetRDFiter->first);

     }

     return listOfProperties;
 }
*/
