#ifndef VISURDFDESSINATEUR_H
#define VISURDFDESSINATEUR_H
#include "visurdfobjet.h"
#include "visurdftype.h"
#include "visurdfanalyseur.h"
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


class VisuRDFDessinateur
{
public:
    VisuRDFDessinateur(VisuRDFAnalyseur* analyseur);
    ~VisuRDFDessinateur();
    float calculLargeurColonne(VisuRDFType* type, string nomPropriete);
    float calculLargeurTableau(VisuRDFType* type);
    int calculHauteurTableau(VisuRDFType* type);
    int calculHauteurDessin();
    void dessinTableau(VisuRDFType* type, int x, int y, QPainter &painter);
    void dessinModeTableau(QPainter& painter);


private :
   // list<Objet> listeObjets;
    set<VisuRDFType*> listeTypes;
    VisuRDFAnalyseur* analyseur;
    int hauteurCase;
    int espacementVertical;
    float pourcentagePolice;
};


#endif // VISURDFDESSINATEUR_H
