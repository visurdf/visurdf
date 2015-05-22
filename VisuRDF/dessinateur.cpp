#include "dessinateur.h"

Dessinateur::Dessinateur(Analyseur * analyseur)
{
    listeObjets = analyseur->getTousLesObjets();
    listeTypes = analyseur->getTousLesTypes();
}

Dessinateur::~Dessinateur()
{

}

int Dessinateur::calculLargeurColonne(Type * type, string nomPropriete){

    int largeur = nomPropriete.size();

    // On cherche tous les objets du type
    for(list<Objet>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++){

        Objet objet = *it;

        // Comparaison types : redéfinir opérateur =
        // ?????????????????????????????????????
        if(objet.getType() == type){

            ObjetRDF::iterator iter = objet.getProprietes().find(nomPropriete);
            if(iter != objet.getProprietes().end()){
                list<string> valeurs = iter->second;

                list<string>::iterator it2 = valeurs.begin();
                string valeur = *it2;

                int largeurValeur = valeur.size();
                if (largeurValeur > largeur)
                    largeur = largeurValeur;

            }
        }

    }

    return largeur;

}
