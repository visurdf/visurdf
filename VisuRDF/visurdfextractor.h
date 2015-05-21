#ifndef VISURDFEXTRACTOR_H
#define VISURDFEXTRACTOR_H

#include <stdio.h>
#include <raptor2.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <map>
#include <list>
#include <set>


using namespace std;

typedef map<string, list < string > > ObjetRDF; // a chaque propriete associe la liste de ses valeurs
typedef map<string,  list < ObjetRDF > > GrapheRDF; // a chaque classe associe la liste de ses instances
typedef map<string,  list < string > > RelationRDF; // a chaque objet associe ses relations


class QName{

private:
    string name;
    string baseuri;
    string delimiteur;
    string datatype;
    const char* delimiteurdiese ;
    const char* delimiteurslash  ;
public:

    QName(){name = ""; baseuri = "";}
    QName(string uri){
        delimiteurdiese ="#";
        delimiteurslash ="/" ;
        size_t pos = uri.find_last_of(delimiteurdiese);
        if(pos == -1){
            pos = uri.find_last_of(delimiteurslash);
            if(pos != -1){
                delimiteur = delimiteurslash;
                baseuri = uri.substr(0,pos+1);
                name = uri.substr(pos+1, uri.size());
            }else
                name = uri;
        }else{
            delimiteur = delimiteurdiese;

            baseuri = uri.substr(0,pos+1);
            name = uri.substr(pos+1, uri.size());
        }
    }
    virtual ~QName(){}
    virtual const string &getName(){ return name;}
    virtual const string &getBaseUri(){ return baseuri;}

    virtual const string &getDatatype(){ return datatype;}

    virtual void setName(const string _name) { this->name = _name;}
    virtual void setBaseUri(const string _baseuri) { this->baseuri = _baseuri;}

    virtual void setDatatype(const string _datatype) { this->datatype = _datatype;}

    virtual const string & toString(){
        string tostring ( baseuri);

        return tostring.append(name).append(" datatype = ").append(datatype);}

};





class VisuRDFExtractor
{
private:


    static vector<string> split(string str, char delimiter);
    static void printVector(string str);
    static void handle_triple(void* user_data, raptor_statement* triple) ;
    static  QName*  getSubject( raptor_statement* triple);
    static  QName*  getObbject( raptor_statement* triple);
    static  QName* getPredicate( raptor_statement* triple);

    void print_object(ObjetRDF _objetRDF);

    void init_rdf_env(char * rdfFile);

    static string baseURI;

    static GrapheRDF grapheRDF;
    static ObjetRDF objetRDF;// objet RDF en cours d extraction
    static RelationRDF relationRDF;



public:

    VisuRDFExtractor();
    void parse_rdf_triple(char * rdfFile);
    void print_map();
    void print_relations();

    set< string > getClasses();

    GrapheRDF getGrapheRDF(){ return grapheRDF;}
    RelationRDF getRelationRDF(){ return relationRDF;}


};

#endif // VISURDFEXTRACTOR_H
