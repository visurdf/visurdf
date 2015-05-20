#include "analyseur.h"
#include "visurdfextractor.h"
#include <list>
#include <map>

using namespace std;

Analyseur::Analyseur(VisuRDFExtractor extractor) {

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

    // instancier un extractor

    GrapheRDF MapDesObjets; //= extractor.getMap();
    int id = 0;

    for (GrapheRDF::iterator itGraphe = MapDesObjets.begin(); itGraphe != MapDesObjets.end(); ) {

        string classe = itGraphe->first;
        list < ObjetRDF > listeObjets = itGraphe->second;
        // contient tous les objets du type "classe"

        for (list< ObjetRDF >::iterator itObjets = listeObjets.begin(); itObjets != listeObjets.end(); itObjets++) {

            id ++;
            ObjetRDF listeProprietes = *itObjets;

            // creation de l'objet
            Objet* nouvelObjet = new Objet(id, classe, listeProprietes);

            // ajout de l'objet a la liste
            tousLesObjets.push_back(*nouvelObjet);
        }

    }



    // creer la liste de classes
    // on récupère la map de l'extracteur
    // pour chaque nouveau type rencontré, on crée un type
    // pour chaque type, on remplit le vecteur des propriétés

    // compter le nombre de propriétés par type
    // pour chaque Type
    // compter le nombre de proprietes
    // setNombreProprietes dans le Type

    // compter le nombre d'objets par type
    // pour chaque Type
    // compter le nombre d'objets
    // setNombreObjets dans le Type

}

Analyseur::~Analyseur() {
}

list<Objet> Analyseur::getTousLesObjets() {
    return tousLesObjets;
}

list<Type> Analyseur::getTousLesTypes() {
    return tousLesTypes;
}
