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

    Analyseur* analyseur = new Analyseur(&visuRDFExtractor);

    return 0;

}
