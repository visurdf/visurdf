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

/**
 * @brief VisuRDFType::setProprietes
 * @param proprietes
 */
void VisuRDFType::setProprietes(list<string> proprietes){
    proprietesNonVides = proprietes;
}

/**
 * @brief VisuRDFType::setNbObjet
 * @param nb
 */
void VisuRDFType::setNbObjet(int nb){
    nbObjets = nb;
}

/**
 * @brief VisuRDFType::getNom
 * @return nom du type
 */
string VisuRDFType::getNom(){
    return nomType;
}

/**
 * @brief VisuRDFType::getProprietes
 * @return liste des noms de propriétés du type
 */
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

/**
 * @brief VisuRDFType::getNbObjet
 * @return nombre d'objets du type
 */
int VisuRDFType::getNbObjet(){
    return nbObjets;
}

/**
 * @brief VisuRDFType::getNombreRelations
 * @return nombre de relations du type
 */
int VisuRDFType::getNombreRelations(){
    return nombreRelations;
}

/**
 * @brief VisuRDFType::setNombreRelations
 * @param _nombre
 */
void VisuRDFType::setNombreRelations(int _nombre){
    nombreRelations = _nombre;
}
