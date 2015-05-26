#include "visurdfanalyseur.h"
#include "visurdfextractor.h"


using namespace std;

VisuRDFAnalyseur::VisuRDFAnalyseur(VisuRDFExtractor *extractor) {

    this->extractor = extractor;

}
/*
 *
 *   revu a cause d une boucle infinie
 *
 *
VisuRDFAnalyseur::VisuRDFAnalyseur(VisuRDFExtractor *extractor) {

    /*
    extractor :
      - une map avec tous les objets : (classe, liste de objets de la classe(map de propriétés de l'objet))
      - liste des classes (string)
      - liste des propriétés d'une classe (classe en entrée, liste de string en sortie)


    GrapheRDF mapDesObjets = extractor->getGrapheRDF();
    int id = 0;
    // Pour chaque classe :
    for (GrapheRDF::iterator itGraphe = mapDesObjets.begin(); itGraphe != mapDesObjets.end(); ) {

        cout << "toto" <<endl;

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
            cout << "toto1" <<endl;

            nombreObjetsClasse++;
            id ++;
            ObjetRDF listeProprietesObjet = *itObjets;

            // creation de l'objet
            Objet* nouvelObjet = new Objet(id, nouveauType, listeProprietesObjet);
            // ----> est-ce qu'on met un type au lieu du string pour la classe ?

            // ajout de l'objet a la liste
            tousLesObjets.push_back(*nouvelObjet);

            // ajout des proprietes a la liste proprietesNonVidesDuType
            for (ObjetRDF::iterator itProprietesObjet = listeProprietesObjet.begin(); itProprietesObjet != listeProprietesObjet.end(); itProprietesObjet++) {
                cout << "toto2" <<endl;

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

        */


set<Type* > VisuRDFAnalyseur::getAllTypes(bool withnotnullproperties){

    allTypes.clear();
    GrapheRDF grapheRDF = extractor->getGrapheRDF();

    for (GrapheRDF::const_iterator grapheiter = grapheRDF.begin(); grapheiter != grapheRDF.end(); grapheiter++){

        Type* unType =  getTypeByName(grapheiter->first, withnotnullproperties);

        //            list< ObjetRDF > listOfObjetRDF = grapheiter->second;
        //            // nombre d objets
        //            unType->setNbObjet(listOfObjetRDF.size());
        //            // recuperation de la liste des proprietes y compris celles qui n'ont pas de valeurs significatives
        //            ObjetRDF objetRDF  = *listOfObjetRDF.begin();
        //            set< string > listOfProperties = set< string >();
        //            for (ObjetRDF::const_iterator objetRDFiter = objetRDF.begin(); objetRDFiter != objetRDF.end(); objetRDFiter++){
        //                if(objetRDFiter->first.compare("type") == 0)
        //                    continue;
        //                listOfProperties.insert(objetRDFiter->first);
        //            }

        //            unType->setProprietes(listOfProperties);


        allTypes.insert(unType);

    }




    return allTypes;
}

int VisuRDFAnalyseur::countType(){
    if(allTypes.size() == 0)
        getAllTypes(false);
    return allTypes.size();
}

Type* VisuRDFAnalyseur::getTypeByName(string nameoftype, bool withnotnullproperties){
    Type* unType =  new Type(nameoftype);

    list< ObjetRDF > listOfObjetRDF = extractor->getGrapheRDF()[nameoftype];
    // nombre d objets
    unType->setNbObjet(listOfObjetRDF.size());
    // recuperation de la liste des proprietes y compris celles qui n'ont pas de valeurs significatives
    ObjetRDF objetRDF  = *listOfObjetRDF.begin();
    list< string > listOfProperties = list< string >();
    for (ObjetRDF::const_iterator objetRDFiter = objetRDF.begin(); objetRDFiter != objetRDF.end(); objetRDFiter++){
        if(objetRDFiter->first.compare("type") == 0)
            continue;
        listOfProperties.push_back(objetRDFiter->first);
    }

    list< string > listOfFilterProperties = list< string >();
    if(withnotnullproperties){//filtrage des proprietes sans valeurs significatives
        typedef list<string>::const_iterator ListIterator;
        for (ListIterator list_iter = listOfProperties.begin(); list_iter != listOfProperties.end(); list_iter++)
        {
            string propriete = *list_iter;
            bool isEmpty = false;
            typedef list<ObjetRDF>::const_iterator ListObjetRDFIterator;
            int n = 0;
            for (ListObjetRDFIterator objiter = listOfObjetRDF.begin(); objiter != listOfObjetRDF.end(); objiter++)
            {

                ObjetRDF obj = *objiter;

                list<string> listOfVal = obj[propriete];
                n = listOfVal.size();
                typedef list<string>::const_iterator ListIterator;
                for (ListIterator list_iter = listOfVal.begin(); list_iter != listOfVal.end(); list_iter++){
                    if((*list_iter).compare("") == 0){
                        isEmpty = true;
                        break;
                    }

                }
                if(isEmpty)break;
            }

            if(!isEmpty){
                for(int i =0; i < n; i++)
                    listOfFilterProperties.push_back(propriete);
            }

        }
    }
    if(listOfFilterProperties.size() != 0)
        unType->setProprietes(listOfFilterProperties);
    else
        unType->setProprietes(listOfProperties);
    return unType;
}


VisuRDFAnalyseur::~VisuRDFAnalyseur() {
}

list<Objet> VisuRDFAnalyseur::getTousLesObjets() {
    return tousLesObjets;
}


list<Type> VisuRDFAnalyseur::getTousLesTypes() {
    return tousLesTypes;
}
