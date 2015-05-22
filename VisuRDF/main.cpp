
#include "visurdfextractor.h"
#include <QApplication>
#include "classesvg.h"
#include "analyseur.h"


int main(int argc, char *argv[])
{

    QApplication A(argc,argv);

    VisuRDFExtractor visuRDFExtractor;
    classesvg C;

    visuRDFExtractor.parse_rdf_triple(argv[1]);
    visuRDFExtractor.print_map();
    visuRDFExtractor.print_relations();
    C.drawSvg();

    cout << "\n Classes:\n" << endl;
    set<string > listOfClass = visuRDFExtractor.getClasses();

    for (set<string >::const_iterator grapheiter = listOfClass.begin(); grapheiter != listOfClass.end(); grapheiter++)       {
        //set<string > listOfProperties = visuRDFExtractor.getProperties(*grapheiter);
        cout << *grapheiter << "\t"<< endl;
        //for (set<string >::const_iterator props = listOfProperties.begin(); props != listOfProperties.end(); props++)
          //  cout << *props << "\t";
        //cout << endl<< endl;
    }

    Analyseur* analyseur = new Analyseur(&visuRDFExtractor);

    return 0;
}



