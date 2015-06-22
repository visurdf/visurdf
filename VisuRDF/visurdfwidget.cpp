#include "visurdfwidget.h"
#include "ui_visurdfwidget.h"
#include "visurdfextracteur.h"
#include "visurdfparametreur.h"
#include <QMessageBox>
#include <QSvgGenerator>

visuRDFWidget::visuRDFWidget()
{
    rdfChoisi = false;
    dessinModifie = false;
    firstDessin = true;
    boiteChoisie = NULL;


}

visuRDFWidget::~visuRDFWidget()
{

}

/**
 * @brief visuRDFWidget::paintEvent, redessine le dessin dans la fenetre du widget
 * @param qpe
 */
void visuRDFWidget::paintEvent(QPaintEvent *qpe){
    QWidget::paintEvent(qpe);
    QPainter painter(this);
    //Si il n'y a pas eu de rdf choisi, on ne fait rien
    if (rdfChoisi){
        //Si c'est la premère fois qu'on dessine, on appelle la fonction dessin
        if(firstDessin){
            dessinateur->dessin(painter);
            dessinModifie = false;
            firstDessin = false;
        }
        //Sinon la fonction dessinMap
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
    QFileDialog dialogue;
    QString fileName = dialogue.getOpenFileName(this,"Open File","","RDF files (*.rdf)");

    if (fileName != NULL){

        //On supprime les données déjà présente dans l'extracteur
        VisuRDFExtracteur visuRDFExtracteur;
        visuRDFExtracteur.clearModule();

        //Traitement chaine de caractère pour l'ouverture du fichier
        const char * file = fileName.toStdString().c_str();
        char fileAvecProtocole [strlen(file +8)];
        strcpy(fileAvecProtocole, "file://");
        file = strcat(fileAvecProtocole, file );
        cout<< "chemin : "<< fileAvecProtocole <<endl;

        //création des différents objets necessaires
        visuRDFExtracteur.parserTripletRdf(fileAvecProtocole);
        analyseur = new VisuRDFAnalyseur(&visuRDFExtracteur);
        dessinateur = new VisuRDFDessinateur(analyseur);

        //Mise à jour des booléen de la classe
        rdfChoisi = true;
        dessinModifie = true;
        firstDessin = true;

        this->update();
    }


}

/**
 * @brief visuRDFWidget::print
 * Fonction permettant d'imprimer la figure présente dans la fenêtre au format SVG ou PNG
 */
void visuRDFWidget::print(){


    /*-------------Choix de l'emplacement de l'enregistrement -------------------*/
    QFileDialog fileDialogue(this);


    QString fileName = fileDialogue.getSaveFileName(this,"Choose File","","Format SVG (*.svg);; Format PNG(*.png)");

    //Cas d'un SVG

    if (fileName.contains(".svg")){

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
    //Cas d'un png
    else if (fileName.contains(".png")){
        float hauteur = dessinateur->calculHauteurDessin();
        float largeur = dessinateur->calculLargeurDessin();

        QImage img(largeur,hauteur, QImage::Format_ARGB32);
        QPainter painter;
        painter.begin(&img);
        dessinateur->dessinMap(painter);
        painter.end();
        img.save(fileName);
    }
    //Sinon erreur sur l'extension du fichier
    else
        QMessageBox::warning(this,"erreur","Veuillez saisir une extension correcte");

}

void visuRDFWidget::printPNG(){
    /*-------------Choix de l'emplacement de l'enregistrement -------------------*/

    QString fileName =  QFileDialog::getSaveFileName(this,"Choose File","","PNG files (*.png)");
    //const char * file = fileName.toStdString().c_str();

    float hauteur = dessinateur->calculHauteurDessin();
    float largeur = dessinateur->calculLargeurDessin();

    QImage img(largeur,hauteur, QImage::Format_ARGB32);
    QPainter painter;
    painter.begin(&img);
    dessinateur->dessinMap(painter);
    painter.end();
    img.save(fileName);
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

    //On recupere la boite choisie
    if(!firstDessin){
        boiteChoisie = dessinateur->recupererBoite(posSouris.x(),posSouris.y());
    }
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

        if(!firstDessin)
            dessinateur->actualiserMapBoite(boiteChoisie, posSouris.x(),posSouris.y());

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

    //Si le dessin à été modifié
    if(!firstDessin)
        dessinateur->actualiserMapBoite(boiteChoisie, posSouris.x(),posSouris.y());
    //On relache la boite choisie
    boiteChoisie = NULL;
    dessinModifie=true;
    this->update();
    if (QWidget::hasMouseTracking()){
        QWidget::setMouseTracking(false);
    }
}

/**
 * @brief visuRDFWidget::changeColoration
 * permet de changer la valeur de coloration : 1 = coloration, 0 = pas de coloration
 * @param c
 */
void visuRDFWidget::changeColoration(int c){
    if (!rdfChoisi)
        return;
    dessinateur->setCouleur(c);
    this->update();


}

/**
 * @brief visuRDFWidget::changeMode : permet de changer le mode d'utilisation
 * @param string mode
 */
void visuRDFWidget::changeMode(string mode){
    if (!rdfChoisi)
        return;

    dessinateur->setMode(mode);
    firstDessin = true;
    dessinModifie =true;
    dessinateur->isFirst = true;

    this->update();

}

/**
 * @brief visuRDFWidget::changePolice : permet de changer la police utilisée
 * @param QFont f
 */
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

/**
 * @brief visuRDFWidget::changePourcentagePoliceH
 * Permet de changer le coefficient de Hauteur des boite
 * @param int p
 */
void visuRDFWidget::changePourcentagePoliceH(int p){
    if (!rdfChoisi)
        return;

    dessinateur->setPourcentagePoliceHauteur((float)(p * 0.1));
    this->update();

}

/**
 * @brief visuRDFWidget::changeTaillePolice
 * Permet de changer la taille de la police
 * @param int p
 */
void visuRDFWidget::changeTaillePolice(int p){
    if (!rdfChoisi)
        return;

    dessinateur->setFontSize(p);
    this->update();
}
