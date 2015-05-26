#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <iostream>
#include <set>
#include <objet.h>
#include <type.h>

#include <algorithm> //to use "find"

#include "visurdfextractor.h"

using namespace std;

class VisuRDFAnalyseur
{
public:
    VisuRDFAnalyseur(VisuRDFExtractor *extractor);
    ~VisuRDFAnalyseur();
    std::list<Objet> getTousLesObjets();
    std::list<Type> getTousLesTypes();

    //expose la liste des types
    set<Type* > getAllTypes(bool withnotnullproperties);
    //retoune le nombre de type
    int countType();

    //retourne un type en fonction de son nom
    Type* getTypeByName(string nameoftype,  bool withnotnullproperties);



/*


    //expose la liste des types avec propriete significative
    set<Type> getAllTypes(bool withnotnullproperties);

    //retourne le nombre d'objet d'un type
    int countObjectByType(string nameoftype);
    //retourne l'ensemble des objets d un type
    set<Objet> getObjectByType(string nameoftype);
*/
private:
    //une reference sur l extracteur
    VisuRDFExtractor *extractor;
    //la liste des types
    set<Type* > allTypes;



    std::list<Objet> tousLesObjets;
    std::list<Type> tousLesTypes;
};

#endif // ANALYSEUR_H
