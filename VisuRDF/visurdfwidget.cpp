#include "visurdfwidget.h"
#include "ui_visurdfwidget.h"
#include "visurdfextracteur.h"

visuRDFWidget::visuRDFWidget()
{
    rdfChoisi = false;
    dessinModifie = false;

}

visuRDFWidget::~visuRDFWidget()
{

}

void visuRDFWidget::paintEvent(QPaintEvent *qpe){
    QWidget::paintEvent(qpe);
    QPainter painter(this);

    if (rdfChoisi && dessinModifie){
        cout<< "dans le painter"<<endl;
        dessinateur->dessin(painter);
        dessinModifie = false;
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
    visuRDFExtracteur.parserTripletRdf("2-contextes.rdf");
    visuRDFExtracteur.afficherMap();
    visuRDFExtracteur.afficherRelations();

    analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);
    dessinateur = new VisuRDFDessinateur(analyseur);
    rdfChoisi = true;
    dessinModifie = true;

    this->update();

    //}
}

void visuRDFWidget::print(){

    VisuRDFGenerateur generateur(dessinateur);
    generateur.dessin();
}

/**
 * @brief visuRDFWidget::mousePressEvent
 * @param qme
 * fonction réalisée lors du clic souris
 */
void visuRDFWidget::mousePressEvent(QMouseEvent *qme){
    QWidget::mouseMoveEvent(qme);

    //On met en place le mouse tracking, utilisable dans les autres fonction
    QWidget::setMouseTracking(false);
    cout<<"clic souris" << endl;
    dessinModifie=true;

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
        // A ajouté, traitement sur les positions des boites de l'analyseur

        //On met à jour l'image
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
     if (QWidget::hasMouseTracking()){
         QWidget::setMouseTracking(false);


     }

}
