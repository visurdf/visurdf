#include "visurdfgenerateur.h"

VisuRDFGenerateur::VisuRDFGenerateur(VisuRDFDessinateur *dessinateur) {

    this->dessinateur = dessinateur;

    float hauteur = dessinateur->calculHauteurDessin();
    float largeur = dessinateur->calculLargeurDessin();
    color = Qt::black;
    pen.setColor(color);

    /*------------- Déclaration des paramètres du fichier SVG -------------------*/
    generator.setFileName("testSVG.svg");
    generator.setSize(QSize(largeur, hauteur));
    generator.setViewBox(QRect(0, 0, largeur, hauteur));
    generator.setTitle("SVG Generator Example Drawing");
    generator.setDescription("Dessin svg pour une démonstration");
}

VisuRDFGenerateur::~VisuRDFGenerateur() {

}


/**
 * @brief VisuRDFGenerateur::dessin
 * Crée l'image
 *
 */

void VisuRDFGenerateur::dessin() {

    float hauteur = dessinateur->calculHauteurDessin();
    float largeur = dessinateur->calculLargeurDessin();

    generator.setSize(QSize(largeur, hauteur));
    generator.setViewBox(QRect(0, 0, largeur, hauteur));
    painter.begin(&generator);



    dessinateur->dessin(painter);
    //dessinateur->dessinToutesLiaisons(painter);

    painter.end();
    std::cout<<"Fin du dessin"<<std::endl;
}


