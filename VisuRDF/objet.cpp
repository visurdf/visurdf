#include "objet.h"


// redéfinir copie constructeur?????????????
Objet::Objet(int id, Type *type, ObjetRDF proprietes) : id(id), type(type), proprietes(proprietes)
{

}


Objet::~Objet()
{

}

int Objet::getLargeur(){
    return largeurMax;
}

ObjetRDF Objet::getProprietes(){
    return proprietes;
}

Type *Objet::getType(){
    return type;
}




// Méthode qui va calculer la longueur max de la concaténation "nom propriété', "valeur propriété"
void Objet::setLargeur(){

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
}

string Objet::toString(){

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
