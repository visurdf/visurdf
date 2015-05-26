
#include "visurdfextractor.h"
#include <QApplication>
#include "classesvg.h"
#include "visurdfanalyseur.h"
#include "dessinateur.h"


int main(int argc, char *argv[])
{

    QApplication A(argc,argv);

    VisuRDFExtractor visuRDFExtractor;
   // classesvg C;

    visuRDFExtractor.parse_rdf_triple(argv[1]);
    visuRDFExtractor.print_map();
    visuRDFExtractor.print_relations();
   // C.drawSvg();

    cout << "\n Classes:\n" << endl;
    set<string > listOfClass = visuRDFExtractor.getClasses();

    for (set<string >::const_iterator grapheiter = listOfClass.begin(); grapheiter != listOfClass.end(); grapheiter++)       {
        //set<string > listOfProperties = visuRDFExtractor.getProperties(*grapheiter);
        cout << *grapheiter << "\t"<< endl;
        //for (set<string >::const_iterator props = listOfProperties.begin(); props != listOfProperties.end(); props++)
          //  cout << *props << "\t";
        //cout << endl<< endl;
    }

    VisuRDFAnalyseur* analyseur = new VisuRDFAnalyseur(&visuRDFExtractor);

    Dessinateur* dessinateur = new Dessinateur(analyseur);
     set<Type* > allTypes = analyseur->getAllTypes(false);
     cout << "\n Nbre Types : " << allTypes.size() << endl;
     typedef set<Type* > ::const_iterator ListIterator;
    for(ListIterator itr = allTypes.begin(); itr != allTypes.end(); itr++ )
        cout << (*itr)->toString() << endl;

    allTypes = analyseur->getAllTypes(true);
         cout << "\n Nbre Types avec proprietes significatives: " << allTypes.size() << endl;
         typedef set<Type* > ::const_iterator ListIterator;
        for(ListIterator itr = allTypes.begin(); itr != allTypes.end(); itr++ )
            cout << (*itr)->toString() << endl;


    Type* unType = analyseur->getTypeByName(*listOfClass.begin(), false);

    cout << endl<< endl << unType->toString() << endl;

    unType = analyseur->getTypeByName(*listOfClass.begin(), true);

    cout << endl<< endl << unType->toString() << endl;

    dessinateur->dessinTableau(unType, 20, 20);


    return 0;
}



