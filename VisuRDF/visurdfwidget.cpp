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

    if (rdfChoisi && dessinModifie){
        if(firstDessin){
            cout<< "dans le painter"<<endl;
            dessinateur->dessin(painter);
            dessinModifie = false;
            firstDessin = false;
            cout<< "sortie le painter"<<endl;
        }
        else{
            cout<< "dans le painter2"<<endl;
            dessinateur->dessinMap(painter);
            dessinModifie = false;
            firstDessin = false;
            cout<< "sortie le painter"<<endl;
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
    //visuRDFExtracteur.parserTripletRdf("file:///home/rodrigue/visurdf/VisuRDF/FacetteA test v2.rdf");

    //visuRDFExtracteur.afficherMap();
   // visuRDFExtracteur.afficherRelations();


    analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);
    dessinateur = new VisuRDFDessinateur(analyseur);
    rdfChoisi = true;
    dessinModifie = true;

    this->update();

    //}
}

void visuRDFWidget::print(){



    /*------------- Déclaration des paramètres du fichier SVG -------------------*/
    QSvgGenerator generator;

    float hauteur = dessinateur->calculHauteurDessin();
    float largeur = dessinateur->calculLargeurDessin();
    generator.setFileName("testSVG.svg");
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
    cout<<"clic souris" << endl;
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
        cout << "x : " << posSouris.x() << ",y : " << posSouris.y() <<endl;

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

    cout << "x : " << posSouris.x() << ",y : " << posSouris.y() <<endl;

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
    VisuRDFParametreur *parametreur = dessinateur->getParametreur();
    parametreur->setMode(mode);
    firstDessin = true;
    dessinModifie =true;
    dessinateur->isFirst = true;

    this->update();

}

void visuRDFWidget::changePourcentagePolice(int p){

}

void visuRDFWidget::changePourcentagePoliceH(int p){

}
