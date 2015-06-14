
#include "visurdfextracteur.h"
#include <QApplication>
#include "visurdfclassesvg.h"
#include "visurdfanalyseur.h"
#include "visurdfdessinateur.h"
#include "visurdfgenerateur.h"
#include "visurdfparametreur.h"
#include <QTextCodec>


int main(int argc, char *argv[])
{
    // Encodage UTF-8
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication A(argc,argv);

    VisuRDFExtracteur visuRDFExtracteur;

    visuRDFExtracteur.parserTripletRdf(argv[1]);
    visuRDFExtracteur.afficherMap();
    visuRDFExtracteur.afficherRelations();



    VisuRDFAnalyseur* analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);

     VisuRDFDessinateur* dessinateur = new VisuRDFDessinateur(analyseur);
     VisuRDFGenerateur* generateur = new VisuRDFGenerateur(dessinateur);


    generateur->dessin();



    return 0;
}



