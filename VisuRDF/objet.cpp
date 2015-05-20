#include "objet.h"
#include "visurdfextractor.h"

Objet::Objet(int id, string nomType, ObjetRDF proprietes) : id(id), nomType(nomType), proprietes(proprietes)
{

}


Objet::~Objet()
{

}

void Objet::setLargeur(int l){
    largeurMax = l;
}

