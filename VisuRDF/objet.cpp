#include "objet.h"


Objet::Objet(int id, string nomType, proprieteMap proprietes) : id(id), nomType(nomType), proprietes(proprietes)
{

}


Objet::~Objet()
{

}

int Objet::getLargeur(){
    return largeurMax;
}

proprieteMap Objet::getProprietes(){
    return proprietes;
}

string Objet::getNomType(){
    return nomType;
}

// Méthode qui va calculer la longueur max de la concaténation "nom propriété', "valeur propriété"
void Objet::setLargeur(){

    // On initialise largeur avec la longueur du string "nomType"
    int largeur = nomType.size();

    // On parcourt la map "proprietes" et on créé une liste de string en concaténant

    list<string> proprieteConcatenee ;

    for(proprieteMap::const_iterator it = proprietes.begin(); it!=proprietes.end(); it++){
        string nom = it->first;
        string valeur = it->second;
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
}
