
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
    set<string > listOfClass = visuRDFExtracteur.getClasses();

    for (set<string >::const_iterator grapheiter = listOfClass.begin(); grapheiter != listOfClass.end(); grapheiter++)       {
        //set<string > listOfProperties = visuRDFExtractor.getProperties(*grapheiter);
        cout << *grapheiter << "\t"<< endl;
        //for (set<string >::const_iterator props = listOfProperties.begin(); props != listOfProperties.end(); props++)
          //  cout << *props << "\t";
        //cout << endl<< endl;
    }

    VisuRDFAnalyseur* analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);


     set<VisuRDFType*> allTypes = analyseur->getTousLesTypes(false);
     cout << "\n Nbre Types : " << allTypes.size() << endl;
     typedef set<VisuRDFType* > ::const_iterator ListIterator;
    for(ListIterator itr = allTypes.begin(); itr != allTypes.end(); itr++ )
        cout << (*itr)->toString() << endl;

    allTypes = analyseur->getTousLesTypes(true);
         cout << "\n Nbre Types avec proprietes significatives: " << allTypes.size() << endl;
         typedef set<VisuRDFType* > ::const_iterator ListIterator;
        for(ListIterator itr = allTypes.begin(); itr != allTypes.end(); itr++ )
            cout << (*itr)->toString() << endl;


    VisuRDFType* unType = analyseur->getTypeParNom(*listOfClass.begin(), false);

    cout << endl<< endl << unType->toString() << endl;

    unType = analyseur->getTypeParNom(*listOfClass.begin(), true);

    cout << endl<< endl << unType->toString() << endl;

   set<VisuRDFObjet*>listOfObject = analyseur->getObjetsParType(*listOfClass.begin(), true);
   typedef set<VisuRDFObjet* > ::const_iterator ObjectIterator;
  for(ObjectIterator itr = listOfObject.begin(); itr != listOfObject.end(); itr++ )
    cout << (*itr)->toString() << endl;

    VisuRDFDessinateur* dessinateur = new VisuRDFDessinateur(analyseur);
    VisuRDFGenerateur* generateur = new VisuRDFGenerateur(dessinateur);
    //generateur->dessinTableau(unType, 20, 20);
    generateur->dessin();
   // dessinateur->dessinTableau(unType, 20, 20);
  //  cout << "largeur tableau : " << dessinateur->calculLargeurColonne(unType, "Equipement.port") << endl;

    return 0;
}



