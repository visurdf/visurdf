#ifndef VISURDFGENERATEUR_H
#define VISURDFGENERATEUR_H

#include <QSvgRenderer>
#include <QSvgGenerator>
#include "visurdfdessinateur.h"

class VisuRDFGenerateur
{
public:
    VisuRDFGenerateur(VisuRDFDessinateur* dessinateur, VisuRDFParametreur* parametreur);
    ~VisuRDFGenerateur();
    void dessin();
    void dessinTableau(VisuRDFType* type, int x, int y);
    void dessinBoite(VisuRDFObjet* objet, int x, int y);
    void dessinBoiteParType(VisuRDFType* type, int x, int y);
    void dessinModeBoite();

private :
    VisuRDFDessinateur* dessinateur;
    VisuRDFParametreur* parametreur;
    QPainter painter;
    QSvgGenerator generator;
    QPen pen;
    QColor color;
};

#endif // VISURDFGENERATEUR_H
