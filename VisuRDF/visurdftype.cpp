#include "visurdftype.h"
using namespace std;

VisuRDFType::VisuRDFType(string nomType) : nomType(nomType)
{
    nombreRelations = 0;

}

VisuRDFType::~VisuRDFType()
{
    nombreRelations = 0;
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

    // Si il y a bien une propriété "name", on la met en première position
    bool name = false;
    for(list<string>::iterator it = proprietesNonVides.begin(); it!=proprietesNonVides.end(); it++){
        string nomPropriete = *it;
        if(nomPropriete=="name")
            name = true;
    }

    if(name){
    proprietesNonVides.remove("name");
    proprietesNonVides.push_front("name");
    }

    return proprietesNonVides;
}

int VisuRDFType::getNbObjet(){
    return nbObjets;
}

int VisuRDFType::getNombreRelations(){
    return nombreRelations;
}

void VisuRDFType::setNombreRelations(int _nombre){
    nombreRelations = _nombre;
}
