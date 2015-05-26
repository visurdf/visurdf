#include "generateur.h"

Generateur::Generateur(Dessinateur *dessinateur)
{
    this->dessinateur = dessinateur;

    color = Qt::black;
    pen.setColor(color);

    /*------------- Déclaration des paramètres du fichier SVG -------------------*/
    generator.setFileName("testSVG.svg");
    generator.setSize(QSize(1000, 1000));
    generator.setViewBox(QRect(0, 0, 1000, 1000));
    generator.setTitle("SVG Generator Example Drawing");
    generator.setDescription("Dessin svg pour une démonstration");
}

Generateur::~Generateur()

{

}

void Generateur::dessin(){



    painter.begin(&generator);

    /*------------ Déclaration d'une police utilisable en SVG -------------------*/
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

    painter.end();
    std::cout<<"Fin du dessin"<<std::endl;


}

/*
void Generateur::dessinTableau(Type *type, int x, int y){
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
}*/
