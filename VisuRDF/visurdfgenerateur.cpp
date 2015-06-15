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


/**
 * @brief VisuRDFGenerateur::dessinTableau
 * Dessine sur l'image un tableau pour une classe
 *
 * @param type
 * @param x
 * @param y
 */

void VisuRDFGenerateur::dessinTableau(VisuRDFType *type, int x, int y) {

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

void VisuRDFGenerateur::dessinBoite(VisuRDFObjet *objet, int x, int y){
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

   // dessinateur->dessinBoite(objet, x, y, painter);

    painter.end();
    std::cout<<"Fin du dessin"<<std::endl;
}

void VisuRDFGenerateur::dessinBoiteParType(VisuRDFType *type, int x, int y){

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

   // dessinateur->dessinBoiteParType(type, x, y, painter);

    painter.end();
    std::cout<<"Fin du dessin"<<std::endl;

}

void VisuRDFGenerateur::dessinModeBoite(){
    painter.begin(&generator);

    //Famille de Police
   // QFontDatabase fontDataBase;
   // QString firstFont = fontDataBase.families().first();
   // QFont f(firstFont);

    //Paramètres de la police
  //  int fontSize = 6;
   // f.setPixelSize(fontSize);
   // painter.setPen(pen);
   // painter.setFont(f);

    dessinateur->dessinModeBoite(painter);

  //  dessinateur->dessinToutesLiaisons(painter);

    painter.end();
    std::cout<<"Fin du dessin"<<std::endl;
}
