#ifndef VISURDFANALYSEUR_H
#define VISURDFANALYSEUR_H

#include <iostream>
#include <set>
#include <visurdfobjet.h>
#include <visurdftype.h>

#include <algorithm> //to use "find"

#include "visurdfextracteur.h"

using namespace std;

class VisuRDFAnalyseur
{

public:
    VisuRDFAnalyseur(VisuRDFExtracteur *extracteur);
    ~VisuRDFAnalyseur();
    set<VisuRDFType*> getTousLesTypes(bool sansProprietesNulles);
    int compterTypes();
    VisuRDFType* getTypeParNom(string nomDuType,  bool sansProprietesNulles);
    set<VisuRDFObjet*> getObjetsParType(string nomDuType, bool sansProprietesNulles);

private:
    VisuRDFExtracteur *extracteur;
    set<VisuRDFType*> tousLesTypes;
    static int id;
};

#endif // VISURDFANALYSEUR_H
