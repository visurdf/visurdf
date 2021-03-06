#include "visurdfgenerateur.h"

VisuRDFGenerateur::VisuRDFGenerateur(VisuRDFDessinateur *dessinateur) {

    this->dessinateur = dessinateur;

    int hauteur = dessinateur->calculHauteurDessin();
    color = Qt::black;
    pen.setColor(color);

    /*------------- Déclaration des paramètres du fichier SVG -------------------*/
    generator.setFileName("testSVG.svg");
    generator.setSize(QSize(1000, hauteur));
    generator.setViewBox(QRect(0, 0, 1000, hauteur));
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

    // Début du painter
    painter.begin(&generator);

    //Famille de Police
    QFontDatabase fontDataBase;
    QString firstFont = fontDataBase.families().first();
    QFont f(firstFont);

    //Paramètres de la police
    int fontSize = 6;
    f.setPixelSize(fontSize);
    painter.setPen(pen);
    painter.setFont(f);

    dessinateur->dessinModeTableau(painter);

    // Fin du painter
    painter.end();
    std::cout<<"Fin du dessin"<<std::endl;
}


/**
 * @brief VisuRDFGenerateur::dessinTableau
 * Dessine sur l'image un tableau pour une classe
 *
 * @param type
 * @param x
 * @param y
 */

void VisuRDFGenerateur::dessinTableau(VisuRDFType *type, int x, int y) {

    // Utile pour les tests intermédiaires (à supprimer par la suite?)

    painter.begin(&generator);

    //Famille de Police
    QFontDatabase fontDataBase;
    QString firstFont = fontDataBase.families().first();
    QFont f(firstFont);

    //Paramètres de la police
    int fontSize = 6;
    f.setPixelSize(fontSize);
    painter.setPen(pen);
    painter.setFont(f);

    dessinateur->dessinTableau(type, x, y, painter);
    painter.end();
    std::cout<<"Fin du dessin"<<std::endl;
}
