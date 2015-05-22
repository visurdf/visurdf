#ifndef DESSINATEUR_H
#define DESSINATEUR_H
#include "objet.h"
#include "type.h"
#include "visurdfanalyseur.h"
#include "string"

class Dessinateur
{
public:
    Dessinateur(VisuRDFAnalyseur * analyseur);
    ~Dessinateur();
    int calculLargeurColonne(Type* type, string nomPropriete);


private :
    list<Objet> listeObjets;
    list<Type> listeTypes;
    VisuRDFAnalyseur * analyseur;

};


#endif // DESSINATEUR_H
