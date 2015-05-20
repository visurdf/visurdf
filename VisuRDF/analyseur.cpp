#include "analyseur.h"
#include <list>
using namespace std;

analyseur::analyseur() {

    // extractor :
    // - une map avec tous les objets : (classe, liste de objets de la classe(map de propriétés de l'objet))
    // - liste des classes (string)
    // - liste des propriétés d'une classe (classe en entrée, liste de string en sortie)


    // creer la liste d'objets
    // on récupère la map de l'extracteur
    // pour chaque objet de la map, creer un objet Objet
    // l'ajouter au vecteur

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

analyseur::~analyseur() {
}

list<Objet> analyseur::getTousLesObjets() {
    return tousLesObjets;
}

list<Type> analyseur::getTousLesTypes() {
    return tousLesTypes;
}
