#include "visurdfextractor.h"



int main(int argc, char *argv[])
{

    VisuRDFExtractor visuRDFExtractor;

    visuRDFExtractor.parse_rdf_triple(argv[1]);
    visuRDFExtractor.print_map();
    visuRDFExtractor.print_relations();

    return 0;
}




