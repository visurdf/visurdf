#include "visurdfwidget.h"
#include "ui_visurdfwidget.h"
#include "visurdfextracteur.h"

visuRDFWidget::visuRDFWidget()
{
    rdfChoisi = false;


}

visuRDFWidget::~visuRDFWidget()
{

}

void visuRDFWidget::paintEvent(QPaintEvent *qpe){
    QWidget::paintEvent(qpe);
    QPainter painter(this);

    if (rdfChoisi){
        cout<< "dans le painter"<<endl;
        dessinateur->dessin(painter);
        cout<< "sortie le painter"<<endl;

    }

}

/**
 * @brief visuRDFWidget::open
 * Fonction permettant d'ouvrir un fichier RDF dans la fenêtre
 */
void visuRDFWidget::open(){
    //Boite de dialogue pour selection fichier


    QString fileName =  QFileDialog::getOpenFileName(this,"Open File","","RDF files (*.rdf)");

    VisuRDFExtracteur visuRDFExtracteur;
    const char * file = fileName.toStdString().c_str();

    cout<< "chemin : "<< file <<endl;
    //visuRDFExtracteur.parserTripletRdf("const_cast<char*>(file)");
    visuRDFExtracteur.parserTripletRdf("PTR-2.rdf");
    visuRDFExtracteur.afficherMap();
    visuRDFExtracteur.afficherRelations();


    analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);
    dessinateur = new VisuRDFDessinateur(analyseur);
    rdfChoisi = true;

    this->update();

    //}
}

void visuRDFWidget::print(){

    VisuRDFGenerateur generateur(dessinateur);
    generateur.dessin();
}
