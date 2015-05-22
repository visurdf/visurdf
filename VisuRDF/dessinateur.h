#ifndef DESSINATEUR_H
#define DESSINATEUR_H
#include "objet.h"
#include "type.h"
#include "analyseur.h"
#include "string"

class Dessinateur
{
public:
    Dessinateur(Analyseur * analyseur);
    ~Dessinateur();
    int calculLargeurColonne(Type* type, string nomPropriete);


private :
    list<Objet> listeObjets;
    list<Type> listeTypes;
    Analyseur * analyseur;

};


#endif // DESSINATEUR_H
