#include "visurdfobjet.h"



VisuRDFObjet::VisuRDFObjet( VisuRDFType *type, ObjetRDF proprietes) :  type(type), proprietes(proprietes)
{
nombreRelations = 0;
}


VisuRDFObjet::~VisuRDFObjet()
{
nombreRelations = 0;
}

/**
 * @brief VisuRDFObjet::getNom
 * @return nom de l'objet
 */
string VisuRDFObjet::getNom() {
    ObjetRDF::iterator it = proprietes.find("name");
    list<string> listNom = it->second;
    string nom = listNom.front();
    return nom;
}

/**
 * @brief VisuRDFObjet::getProprietes
 * @return map des propriétés de l'objet
 */
ObjetRDF VisuRDFObjet::getProprietes(){
    return proprietes;
}

/**
 * @brief VisuRDFObjet::getType
 * @return type de l'objet
 */
VisuRDFType *VisuRDFObjet::getType(){
    return type;
}

/**
 * @brief VisuRDFObjet::getNombreRelations
 * @return nombre de relations de l'objet
 */
int VisuRDFObjet::getNombreRelations(){
    return nombreRelations;
}

/**
 * @brief VisuRDFObjet::setNombreRelations
 * @param _nombre
 */
void VisuRDFObjet::setNombreRelations(int _nombre){
    nombreRelations = _nombre;
}

/*
// Méthode qui va calculer la longueur max de la concaténation "nom propriété', "valeur propriété"
void VisuRDFObjet::setLargeur(){

    // On initialise largeur avec la longueur du string "nomType"
    string nomType = type->getNom();
    int largeur = nomType.size();

    // On parcourt la map "proprietes" et on créé une liste de string en concaténant

    list<string> proprieteConcatenee ;

    for(ObjetRDF::const_iterator it = proprietes.begin(); it!=proprietes.end(); it++){
        string nom = it->first;
        list<string> listeValeur = it->second;
        list<string>::iterator it2 = listeValeur.begin();
        string valeur = *it2;
        string concatene = nom + " : " + valeur;
        proprieteConcatenee.push_back(concatene);
    }

    // On parcourt la liste "proprieteConcatenee" et met à jour éventuellement "largeur"
    for(list<string>::iterator it = proprieteConcatenee.begin(); it!= proprieteConcatenee.end(); it++){
        int calcul = (*it).size();
        // On compare à largeur et on met éventuellement à jour
        if(calcul>largeur){
            largeur = calcul;
        }
    }

    largeurMax = largeur;
}*/


string VisuRDFObjet::toString(){

    string tostring = "";
    for (ObjetRDF::const_iterator iter = proprietes.begin(); iter != proprietes.end(); iter++)
    {       
        typedef list<string>::const_iterator ListIterator;

        for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
            tostring.append(iter->first).append(":").append(*list_iter).append("\n");
            //cout << "\t\t"<<  iter->first << " : " << *list_iter << endl;

    }
    return tostring;


}
