#include "analyseur.h"
#include "visurdfextractor.h"
#include <list>
#include <map>

using namespace std;

Analyseur::Analyseur(VisuRDFExtractor *extractor) {

    /*
    extractor :
      - une map avec tous les objets : (classe, liste de objets de la classe(map de propriétés de l'objet))
      - liste des classes (string)
      - liste des propriétés d'une classe (classe en entrée, liste de string en sortie)

    typedef map<string, list < string > > ObjetRDF; // a chaque propriete associe la liste de ses valeurs
    contient toutes les propriétés d'un objet

    typedef map<string,  list < ObjetRDF > > GrapheRDF; // a chaque classe associe la liste de ses instances
    contient toutes les classes, associées aux objets de la classe
    */

    // recuperer la Map GrapheRDF

    GrapheRDF MapDesObjets; //= extractor.getMap();
    int id = 0;

    // Pour chaque classe :
    for (GrapheRDF::iterator itGraphe = MapDesObjets.begin(); itGraphe != MapDesObjets.end(); ) {

        string classe = itGraphe->first;

        // creation du Type classe
        Type* nouveauType = new Type(classe);

        list < ObjetRDF > listeObjets = itGraphe->second;
        // contient tous les objets du type "classe"

        // initialisation des attributs du Type
        int nombreObjetsClasse = 0;
        list < string > proprietesNonVidesDuType; // initialiser liste ?

        // Pour chaque objet de la classe :
        for (list < ObjetRDF >::iterator itObjets = listeObjets.begin(); itObjets != listeObjets.end(); itObjets++) {

            nombreObjetsClasse++;
            id ++;
            ObjetRDF listeProprietesObjet = *itObjets;

            // creation de l'objet
            Objet* nouvelObjet = new Objet(id, classe, listeProprietesObjet);

            // ajout de l'objet a la liste
            tousLesObjets.push_back(*nouvelObjet);

            // ajout de la propriete a la liste proprietesNonVides
            // parcourir les proprietes, pour chacune :
                // si la valeur n'est pas nulle
                // et si elle n'est pas deja dans la liste
                // l'ajouter a la liste

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
