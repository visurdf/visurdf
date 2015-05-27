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
    VisuRDFAnalyseur(VisuRDFExtractor *extracteur);
    ~VisuRDFAnalyseur();

    //retourne l'ensemble des types
    set<Type* > getAllTypes(bool sansProprietesNulles);

    //retoune le nombre de types
    int countType();

    //retourne un type en fonction de son nom
    Type* getTypeByName(string nomDuType,  bool sansProprietesNulles);

    //retourne la liste des objets correspondant au nom de type
    set<Objet*> getObjectByType(string nomDuType, bool sansProprietesNulles);

private:
    //une reference sur l extracteur
    VisuRDFExtractor *extracteur;

    //la liste des types
    set<Type*> tousLesTypes;

    //identifiant des objets
    static int id;
};

#endif // ANALYSEUR_H
