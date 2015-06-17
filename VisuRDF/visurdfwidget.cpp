#include "visurdfwidget.h"
#include "ui_visurdfwidget.h"
#include "visurdfextracteur.h"
#include "visurdfparametreur.h"

visuRDFWidget::visuRDFWidget()
{
    rdfChoisi = false;
    dessinModifie = false;
    firstDessin = true;


}

visuRDFWidget::~visuRDFWidget()
{

}

void visuRDFWidget::paintEvent(QPaintEvent *qpe){
    QWidget::paintEvent(qpe);
    QPainter painter(this);
    //this->setMinimumSize(10000, 10000);
    if (rdfChoisi){
        if(firstDessin){
            dessinateur->dessin(painter);
            dessinModifie = false;
            firstDessin = false;
        }

        else{
            dessinateur->dessinMap(painter);
            dessinModifie = false;
            firstDessin = false;
        }
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

    char fileAvecProtocole [strlen(file +8)];
    strcpy(fileAvecProtocole, "file://");
    file = strcat(fileAvecProtocole, file );
    cout<< "chemin : "<< fileAvecProtocole <<endl;
    visuRDFExtracteur.parserTripletRdf(fileAvecProtocole);

    analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);
    dessinateur = new VisuRDFDessinateur(analyseur);
    rdfChoisi = true;
    dessinModifie = true;

    this->update();

}

void visuRDFWidget::print(){


    /*-------------Choix de l'emplacement de l'enregistrement -------------------*/
    QString fileName =  QFileDialog::getSaveFileName(this,"Choose File","","SVG files (*.svg)");
    //const char * file = fileName.toStdString().c_str();

    /*------------- Déclaration des paramètres du fichier SVG -------------------*/


    QSvgGenerator generator;
    float hauteur = dessinateur->calculHauteurDessin();
    float largeur = dessinateur->calculLargeurDessin();
    generator.setFileName(fileName);
    generator.setSize(QSize(largeur, hauteur));
    generator.setViewBox(QRect(0, 0, largeur, hauteur));
    generator.setTitle("SVG Generator Example Drawing");
    generator.setDescription("Dessin svg pour une démonstration");
    QPainter painter;
    painter.begin(&generator);
    dessinateur->dessinMap(painter);
    painter.end();

}

/**
 * @brief visuRDFWidget::mousePressEvent
 * @param qme
 * fonction réalisée lors du clic souris
 */
void visuRDFWidget::mousePressEvent(QMouseEvent *qme){
    QWidget::mousePressEvent(qme);

    //On met en place le mouse tracking, utilisable dans les autres fonction
    QWidget::setMouseTracking(true);
    posSouris = qme->pos();
    xOrigine = posSouris.x();
    yOrigine = posSouris.y();

    dessinModifie=true;
    this->update();

}

/**
 * @brief visuRDFWidget::mouseMoveEvent
 * @param qme
 * Fonction réalisée lors d'un mouvement de souris
 */
void visuRDFWidget::mouseMoveEvent(QMouseEvent *qme){
    QWidget::mouseMoveEvent(qme);
    //Si on a clické et pas relaché on met à jour la position de la souris
    if (QWidget::hasMouseTracking()){
        posSouris = qme->pos();// On réupère la position de la souris dans un QPoint
        xOrigine = posSouris.x();
        yOrigine = posSouris.y();

        if(!firstDessin)
            dessinateur->actualiserMapBoite(xOrigine,yOrigine, posSouris.x(),posSouris.y());

        dessinModifie=true;
        this->update();
    }
}

/**
 * @brief visuRDFWidget::mouseReleaseEvent
 * @param qme
 * Fonction réalisée lors du relachement du bouton de la souris
 */
void visuRDFWidget::mouseReleaseEvent(QMouseEvent *qme){
    QWidget::mouseReleaseEvent(qme);
    posSouris = qme->pos();


    if(!firstDessin)
        dessinateur->actualiserMapBoite(xOrigine,yOrigine, posSouris.x(),posSouris.y());

    dessinModifie=true;
    this->update();
    if (QWidget::hasMouseTracking()){
        QWidget::setMouseTracking(false);
    }
}

void visuRDFWidget::changeColoration(int c){

}

void visuRDFWidget::changeMode(string mode){
    if (!rdfChoisi)
        return;

    VisuRDFParametreur *parametreur = dessinateur->getParametreur();
    parametreur->setMode(mode);
    firstDessin = true;
    dessinModifie =true;
    dessinateur->isFirst = true;

    this->update();

}

void visuRDFWidget::changePolice(QFont f){
    if (!rdfChoisi)
        return;

    dessinateur->setFont(f);
    this->update();
}

void visuRDFWidget::changePourcentagePolice(int p){
    if (!rdfChoisi)
        return;

    dessinateur->setPourcentagePolice((float)(p * 0.1));
    this->update();

}

void visuRDFWidget::changePourcentagePoliceH(int p){
    if (!rdfChoisi)
        return;

    dessinateur->setPourcentagePoliceHauteur((float)(p * 0.1));
    this->update();

}

void visuRDFWidget::changeTaillePolice(int p){
    if (!rdfChoisi)
        return;

    dessinateur->setFontSize(p);
    this->update();
}
