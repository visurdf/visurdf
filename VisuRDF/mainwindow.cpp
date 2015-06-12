#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visurdfextracteur.h"
#include "visurdfclassesvg.h"
#include "visurdfanalyseur.h"
#include "visurdfdessinateur.h"
#include "visurdfgenerateur.h"
#include "visurdfparametreur.h"
#include <QTextCodec>
#include "visurdfwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*Déclaration du widget*/
    // Encodage UTF-8
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    VisuRDFExtracteur visuRDFExtracteur;
    // classesvg C;

    visuRDFExtracteur.parserTripletRdf("2-contextes.rdf");
    visuRDFExtracteur.afficherMap();
    visuRDFExtracteur.afficherRelations();
    // C.drawSvg();



    VisuRDFAnalyseur* analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);




     VisuRDFDessinateur* dessinateur = new VisuRDFDessinateur(analyseur);
     VisuRDFGenerateur* generateur = new VisuRDFGenerateur(dessinateur);


    //generateur->dessinBoiteParType(unType, 20, 20);
    generateur->dessin();


    //generateur->dessinTableau(unType, 20, 20);
    //generateur->dessin();


      RDFWidget = new visuRDFWidget(dessinateur);
      setCentralWidget(RDFWidget);




}

MainWindow::~MainWindow()
{
    delete ui;
}
