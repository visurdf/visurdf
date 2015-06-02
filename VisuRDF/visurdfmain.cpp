
#include "visurdfextracteur.h"
#include <QApplication>
#include "visurdfclassesvg.h"
#include "visurdfanalyseur.h"
#include "visurdfdessinateur.h"
#include "visurdfgenerateur.h"


int main(int argc, char *argv[])
{

    QApplication A(argc,argv);

    VisuRDFExtracteur visuRDFExtracteur;
    // classesvg C;

    visuRDFExtracteur.parserTripletRdf(argv[1]);
    visuRDFExtracteur.afficherMap();
    visuRDFExtracteur.afficherRelations();
    // C.drawSvg();

    cout << "\n Classes:\n" << endl;
    set<string > listeDesClasses = visuRDFExtracteur.getClasses();

    for (set<string >::const_iterator grapheIter = listeDesClasses.begin(); grapheIter != listeDesClasses.end(); grapheIter++)       {
        //set<string > listOfProperties = visuRDFExtractor.getProperties(*grapheiter);
        cout << *grapheIter << "\t"<< endl;
        //for (set<string >::const_iterator props = listOfProperties.begin(); props != listOfProperties.end(); props++)
        //  cout << *props << "\t";
        //cout << endl<< endl;
    }

    VisuRDFAnalyseur* analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);
    set<VisuRDFType*> tousLesTypes = analyseur->getTousLesTypes(false);
    cout << "\n Nbre Types : " << tousLesTypes.size() << endl;

    typedef set<VisuRDFType*> ::const_iterator ListIterator;
    for(ListIterator itr = tousLesTypes.begin(); itr != tousLesTypes.end(); itr++ )
        cout << (*itr)->toString() << endl;

    tousLesTypes = analyseur->getTousLesTypes(true);
    cout << "\n Nbre Types avec proprietes significatives: " << tousLesTypes.size() << endl;
    typedef set<VisuRDFType*> ::const_iterator ListIterator;
    for(ListIterator itr = tousLesTypes.begin(); itr != tousLesTypes.end(); itr++ )
        cout << (*itr)->toString() << endl;

    VisuRDFType* unType = analyseur->getTypeParNom(*listeDesClasses.begin(), false);
    cout << endl<< endl << unType->toString() << endl;

    unType = analyseur->getTypeParNom(*listeDesClasses.begin(), true);
    cout << endl<< endl << unType->toString() << endl;

     VisuRDFDessinateur* dessinateur = new VisuRDFDessinateur(analyseur);
     VisuRDFGenerateur* generateur = new VisuRDFGenerateur(dessinateur);

  /*  set<VisuRDFObjet*>listeDesObjets = analyseur->getObjetsParType(*listeDesClasses.begin(), true);
    typedef set<VisuRDFObjet* > ::const_iterator ObjectIterator;
    for(ObjectIterator itr = listeDesObjets.begin(); itr != listeDesObjets.end(); itr++ ){

        cout << (*itr)->toString() << endl;
      //  cout << "largeur boite : " <<dessinateur->calculLargeurBoite(*itr) << endl;
      //  cout << "hauteur boite : " << dessinateur->calculHauteurBoite(*itr) << endl;
     //   generateur->dessinBoite((*itr), 20, 20);

    }*/

    //generateur->dessinBoiteParType(unType, 20, 20);
    generateur->dessin();
    //generateur->dessinTableau(unType, 20, 20);
    //generateur->dessin();
    // dessinateur->dessinTableau(unType, 20, 20);
    //  cout << "largeur tableau : " << dessinateur->calculLargeurColonne(unType, "Equipement.port") << endl;

    return 0;
}



