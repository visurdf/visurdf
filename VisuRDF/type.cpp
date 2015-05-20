#include "type.h"
using namespace std;

Type::Type(QString nomType) : nomType(nomType)
{

}

Type::~Type()
{

}

void Type::setProprietes(list<QString> proprietes){
    proprietesNonVides = proprietes;
}

void Type::setNbObjet(int nb){
    nbObjets = nb;
}

QString Type::getNom(){
    return nomType;
}

list<QString> Type::getProprietes(){
    return proprietesNonVides;
}

int Type::getNbObjet(){
    return nbObjets;
}
