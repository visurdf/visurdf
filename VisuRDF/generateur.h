#ifndef GENERATEUR_H
#define GENERATEUR_H

#include <QSvgRenderer>
#include <QSvgGenerator>
#include "dessinateur.h"


class Generateur
{
public:
    Generateur(Dessinateur* dessinateur);
    ~Generateur();
    void dessin();
    void dessinTableau(Type* type, int x, int y);

private :
    Dessinateur* dessinateur;
    QPainter painter;
    QSvgGenerator generator;
    QPen pen;
    QColor color;
};

#endif // GENERATEUR_H
