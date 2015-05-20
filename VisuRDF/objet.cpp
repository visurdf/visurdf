#include "objet.h"

Objet::Objet(int id, QString nomType, QMap<QString,QString> proprietes) : id(id), nomType(nomType), proprietes(proprietes)
{

}


Objet::~Objet()
{

}

void Objet::setLargeur(int l){
    largeurMax = l;
}

