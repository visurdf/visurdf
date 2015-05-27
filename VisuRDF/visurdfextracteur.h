#ifndef VISURDFEXTRACTEUR_H
#define VISURDFEXTRACTEUR_H

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

typedef map< string, list <string> > ObjetRDF; // a chaque propriete associe la liste de ses valeurs
typedef map< string,  list <ObjetRDF> > GrapheRDF; // a chaque classe associe la liste de ses instances
typedef map< string,  list <string> > RelationRDF; // a chaque objet associe ses relations


class QName
{
public:
    QName() { nom = ""; uriDeBase = ""; }
    QName(string uri) {
        delimiteurDiese ="#";
        delimiteurSlash ="/";
        size_t pos = uri.find_last_of(delimiteurDiese);
        if(pos == -1) {
            pos = uri.find_last_of(delimiteurSlash);
            if(pos != -1){
                delimiteur = delimiteurSlash;
                uriDeBase = uri.substr(0,pos+1);
                nom = uri.substr(pos+1, uri.size());
            } else
                nom = uri;
        } else {
            delimiteur = delimiteurDiese;
            uriDeBase = uri.substr(0,pos+1);
            nom = uri.substr(pos+1, uri.size());
        }
    }
    virtual ~QName() {}
    virtual const string &getNom() { return nom; }
    virtual const string &getUriDeBase() { return uriDeBase; }
    virtual const string &getTypeDeDonnee() { return typeDeDonnee; }
    virtual const string &toString() {
        string tostring (uriDeBase);
        return tostring.append(nom).append(" type de donnee = ").append(typeDeDonnee); }

    virtual void setNom(const string _nom) { this->nom = _nom; }
    virtual void setUriDeBase(const string _uriDeBase) { this->uriDeBase = _uriDeBase; }
    virtual void setTypeDeDonnee(const string _typeDeDonnee) { this->typeDeDonnee = _typeDeDonnee; }

private:
    string nom;
    string uriDeBase;
    string delimiteur;
    string typeDeDonnee;
    const char* delimiteurDiese;
    const char* delimiteurSlash;
};


class VisuRDFExtracteur
{
public:
    VisuRDFExtracteur();
    void afficherMap();
    void afficherRelations();
    void parserTripletRdf(char* fichierRdf);
    set<string> getClasses();
    GrapheRDF getGrapheRDF() { return grapheRDF; }
    RelationRDF getRelationRDF() { return relationRDF; }

private:
    static vector<string> split(string str, char delimiteur);
    static void afficherVecteur(string str);
    static QName* getSujet(raptor_statement* triple);
    static  QName*  getObjet(raptor_statement* triple);
    static  QName* getPredicat(raptor_statement* triple);
    void afficherObjet(ObjetRDF _objetRDF);
    static void gestionnaireDeTriplets(void* donnee_utilisateur, raptor_statement* triple);
    void initRdfEnvironnement(char * rdfFile);

    // objet RDF en cours d extraction
    static ObjetRDF objetRDF;
    static string uriDeBase;
    static GrapheRDF grapheRDF;
    static RelationRDF relationRDF;

};

#endif // VISURDFEXTRACTEUR_H
