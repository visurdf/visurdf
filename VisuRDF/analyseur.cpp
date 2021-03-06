#include "analyseur.h"
#include "visurdfextractor.h"
#include <list>
#include <map>
#include <algorithm> //to use "find"

using namespace std;

Analyseur::Analyseur(VisuRDFExtractor *extractor) {

    /*
    extractor :
      - une map avec tous les objets : (classe, liste de objets de la classe(map de propriétés de l'objet))
      - liste des classes (string)
      - liste des propriétés d'une classe (classe en entrée, liste de string en sortie)
*/

    GrapheRDF mapDesObjets; // = extractor.getMap();
    int id = 0;

    // Pour chaque classe :
    for (GrapheRDF::iterator itGraphe = mapDesObjets.begin(); itGraphe != mapDesObjets.end(); ) {

        string classe = itGraphe->first;

        // creation du Type classe
        Type* nouveauType = new Type(classe);

        list < ObjetRDF > listeObjets = itGraphe->second;
        // contient tous les objets du type "nouveauType"

        // initialisation des attributs du Type
        int nombreObjetsClasse = 0;
        list < string > proprietesNonVidesDuType; // initialiser liste ?

        // Pour chaque objet du type :
        for (list < ObjetRDF >::iterator itObjets = listeObjets.begin(); itObjets != listeObjets.end(); itObjets++) {

            nombreObjetsClasse++;
            id ++;
            ObjetRDF listeProprietesObjet = *itObjets;

            // creation de l'objet
            Objet* nouvelObjet = new Objet(id, nouveauType, listeProprietesObjet);

            // ajout de l'objet a la liste
            tousLesObjets.push_back(*nouvelObjet);

            // ajout des proprietes a la liste proprietesNonVidesDuType
            for (ObjetRDF::iterator itProprietesObjet = listeProprietesObjet.begin(); itProprietesObjet != listeProprietesObjet.end(); ) {
                string propriete = itProprietesObjet->first;
                list < string > listeValeurs = itProprietesObjet->second;

                if (!listeValeurs.empty()) { // liste non vide
                    if (find(proprietesNonVidesDuType.begin(), proprietesNonVidesDuType.end(), propriete) == proprietesNonVidesDuType.end()){
                        //La liste ne contient pas la propriete, donc on l'ajoute
                        proprietesNonVidesDuType.push_back(propriete);
                    }
                }
            }
        }

        nouveauType->setNbObjet(nombreObjetsClasse);
        nouveauType->setProprietes(proprietesNonVidesDuType);
        tousLesTypes.push_back(*nouveauType);
    }

}

Analyseur::~Analyseur() {
}

list<Objet> Analyseur::getTousLesObjets() {
    return tousLesObjets;
}


list<Type> Analyseur::getTousLesTypes() {
    return tousLesTypes;
}
