#include "classesvg.h"
#include <QRect>
#include <QPainter>
#include <stdio.h>
#include <QFileDialog>
#include <QString>
#include <QTextBlock>
#include <QPainterPath>
#include <QPen>
#include <iostream>
#include <QFontDatabase>


classesvg::classesvg()
{
    color = Qt::red;
    pen.setColor(color);

    /*------------- Déclaration des paramètres du fichier SVG -------------------*/
    generator.setFileName("/home/genne/Documents/Clem/inf380/visurdf/testSVG.svg");
    generator.setSize(QSize(400, 400));
    generator.setViewBox(QRect(0, 0, 400, 400));
    generator.setTitle("SVG Generator Example Drawing");
    generator.setDescription("Dessin svg pour une démonstration");

    /*Parametre du rectangle*/

    Firstleft   = 20;
    FirstTop    = 20;
    largeur     = 100;
    hauteur     = 50;
}

classesvg::~classesvg()
{

}

void classesvg::drawSvg(){

    std::cout<<  "debut de la fonction"<<std::endl;

    /* -------------- Réalisation du dessin -----------------*/

    //debut du painter
    painter1.begin(&generator);

    /*------------ Déclaration d'une police utilisable en SVG -------------------*/
    //Famille de Police
    QFontDatabase fontDataBase;
    QString firstFont = fontDataBase.families().first();
    std::cout << "Police d ecriture : " <<firstFont.toStdString() <<std::endl;
    QFont f(firstFont);

    //Paramètres de la police
    int fontSize = 20;
    f.setPixelSize(fontSize);
    painter1.setPen(pen);
    painter1.setFont(f);

    drawRect(5);

    //dessin des différents élements

//fin du painter
    painter1.end();
    std::cout<<"Fin du dessin"<<std::endl;

}

void classesvg::changeColor(QColor _color){
    color = _color;
    pen.setColor(color);
    painter1.setPen(pen);

}


void classesvg::drawRect(int nbr){

    for (int i = 0; i < nbr; i++){
        QRect rect(Firstleft,FirstTop,largeur,hauteur);
        painter1.drawRect(rect);
        painter1.drawText(Firstleft + 20, FirstTop + 20,"Rectangle3");
        FirstTop += 50;
    }
}
