#ifndef VISURDFCLASSESVG_H
#define VISURDFCLASSESVG_H

#include <QSvgRenderer>
#include <QSvgGenerator>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QPainter>


class visuRDFClasseSvg
{
public:
    visuRDFClasseSvg();
    ~visuRDFClasseSvg();

    void drawSvg();
    void drawRect(int nbr);
    void changeColor(QColor _color);

private:

    QSvgGenerator generator;

    QPainter painter1;
    QPen pen;
    QColor color;
    int Firstleft;
    int FirstTop;
    int largeur;
    int hauteur;

public slots:
};

#endif // VISURDFCLASSESVG_H
