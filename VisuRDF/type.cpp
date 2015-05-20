#include "type.h"
using namespace std;

Type::Type(string nomType) : nomType(nomType)
{

}

Type::~Type()
{

}

void Type::setProprietes(list<string> proprietes){
    proprietesNonVides = proprietes;
}

void Type::setNbObjet(int nb){
    nbObjets = nb;
}

string Type::getNom(){
    return nomType;
}

list<string> Type::getProprietes(){
    return proprietesNonVides;
}

int Type::getNbObjet(){
    return nbObjets;
}
