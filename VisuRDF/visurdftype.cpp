#include "visurdftype.h"
using namespace std;

VisuRDFType::VisuRDFType(string nomType) : nomType(nomType)
{

}

VisuRDFType::~VisuRDFType()
{

}

void VisuRDFType::setProprietes(list<string> proprietes){
    proprietesNonVides = proprietes;
}

void VisuRDFType::setNbObjet(int nb){
    nbObjets = nb;
}

string VisuRDFType::getNom(){
    return nomType;
}

list<string> VisuRDFType::getProprietes(){
    return proprietesNonVides;
}

int VisuRDFType::getNbObjet(){
    return nbObjets;
}
