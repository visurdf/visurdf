#include "visurdfanalyseur.h"
#include "visurdfextracteur.h"


using namespace std;

VisuRDFAnalyseur::VisuRDFAnalyseur(VisuRDFExtracteur *extracteur) {
    this->extracteur = extracteur;
}


/**
 * @brief VisuRDFAnalyseur::getTousLesTypes
 *
 * @param sansProprietesNulles : avec ou sans les propriétés nulles
 * @return set<Type*>, l'ensemble de tous les types
 */

set<VisuRDFType*> VisuRDFAnalyseur::getTousLesTypes(bool sansProprietesNulles) {

    tousLesTypes.clear();
    GrapheRDF grapheRDF = extracteur->getGrapheRDF();

    for (GrapheRDF::const_iterator grapheIter = grapheRDF.begin(); grapheIter != grapheRDF.end(); grapheIter++){

        VisuRDFType* unType =  getTypeParNom(grapheIter->first, sansProprietesNulles);

        tousLesTypes.insert(unType);
    }
    return tousLesTypes;
}


/**
 * @brief VisuRDFAnalyseur::compterTypes
 * @return le nombre de types
 */

int VisuRDFAnalyseur::compterTypes() {
    if(tousLesTypes.size() == 0)
        getTousLesTypes(false);
    return tousLesTypes.size();
}


/**
 * @brief VisuRDFAnalyseur::getTypeParNom
 * @param nomDuType
 * @param sansProprietesNulles : avec ou sans les propriétés nulles
 * @return un pointeur vers le type recherché
 */

VisuRDFType* VisuRDFAnalyseur::getTypeParNom(string nomDuType, bool sansProprietesNulles) {

    VisuRDFType* unType =  new VisuRDFType(nomDuType);

    list<ObjetRDF> listeObjetsRDF = extracteur->getGrapheRDF()[nomDuType];
    // nombre d objets
    unType->setNbObjet(listeObjetsRDF.size());

    // recuperation de la liste des proprietes y compris celles qui n'ont pas de valeurs significatives
    ObjetRDF objetRDF  = *listeObjetsRDF.begin();
    list<string> ListeProprietes = list<string>();

    for (ObjetRDF::const_iterator objetRDFiter = objetRDF.begin(); objetRDFiter != objetRDF.end(); objetRDFiter++){
        if(objetRDFiter->first.compare("type") == 0)
            continue;
        ListeProprietes.push_back(objetRDFiter->first);
    }

    list<string> ListeProprietesFiltrees = list<string>();
    //filtrage des proprietes sans valeurs significatives
    if(sansProprietesNulles){
        typedef list<string>::const_iterator ListIterator;
        for (ListIterator listIter = ListeProprietes.begin(); listIter != ListeProprietes.end(); listIter++)
        {
            string propriete = *listIter;
            bool isEmpty = false;
            typedef list<ObjetRDF>::const_iterator ListObjetRDFIterator;
            int n = 0;
            for (ListObjetRDFIterator objIter = listeObjetsRDF.begin(); objIter != listeObjetsRDF.end(); objIter++)
            {

                ObjetRDF obj = *objIter;

                list<string> listeValeurs = obj[propriete];
                n = listeValeurs.size();
                typedef list<string>::const_iterator ListIterator;
                for (ListIterator listIter = listeValeurs.begin(); listIter != listeValeurs.end(); listIter++){
                    if((*listIter).compare("") == 0){
                        isEmpty = true;
                        break;
                    }
                }
                if(isEmpty)break;
            }

            if(!isEmpty){
                for(int i =0; i < n; i++)
                    ListeProprietesFiltrees.push_back(propriete);
            }
        }
    }

    if(ListeProprietesFiltrees.size() != 0)
        unType->setProprietes(ListeProprietesFiltrees);
    else
        unType->setProprietes(ListeProprietes);

    return unType;
}


/**
 * @brief VisuRDFAnalyseur::id
 * Variable statique permettant de créer un identifiant pour chaque nouvel objet
 */

int VisuRDFAnalyseur::id = 1;


/**
 * @brief VisuRDFAnalyseur::getObjetsParType
 * @param nomDuType
 * @param sansProprietesNulles
 * @return set<Objet*> l'ensemble des objets du type recherché
 */

set<VisuRDFObjet*> VisuRDFAnalyseur::getObjetsParType(string nomDuType, bool sansProprietesNulles) {

    set<VisuRDFObjet*>  listeObjets = set<VisuRDFObjet*>();
    VisuRDFType* unType =  getTypeParNom(nomDuType, sansProprietesNulles);

    list<ObjetRDF> listeObjetsRDF = extracteur->getGrapheRDF()[nomDuType];
    typedef list<ObjetRDF>::const_iterator ListObjetRDFIterator;

    for (ListObjetRDFIterator objIter = listeObjetsRDF.begin(); objIter != listeObjetsRDF.end(); objIter++)
    {
        listeObjets.insert(new VisuRDFObjet(id++, unType, *objIter));
    }

    return listeObjets;
}


VisuRDFAnalyseur::~VisuRDFAnalyseur() {

}
