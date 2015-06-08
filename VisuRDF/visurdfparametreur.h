#ifndef VISURDFPARAMETREUR_H
#define VISURDFPARAMETREUR_H


#include <QtXml>
#include "string"
#include <QPainter>
#include <QRect>
#include <stdio.h>
#include <QFileDialog>
#include <QString>
#include <QTextBlock>
#include <QPainterPath>
#include <QPen>
#include <iostream>
#include <QFontDatabase>
#include <QPaintEvent>
#include <QWidget>



using namespace std;

class VisuRDFParametreur : public QWidget
{
public:
    VisuRDFParametreur();
    ~VisuRDFParametreur();

    void lectureParametres();
    QColor getParamCouleur();
    QPen getParamPen();
    QFont getParamPolice();
    int getParamInterligne();
    int getParamColoration();
    int getFontSize();
    string getParamMode();

private:
    QColor couleur;
    QPen pen;

    QFont police;
    int fontSize;
    int interligne;
    string mode;
    int coloration;
};



#endif // VISURDFPARAMETREUR_H
