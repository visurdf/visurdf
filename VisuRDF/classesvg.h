#ifndef CLASSESVG_H
#define CLASSESVG_H

#include <QSvgRenderer>
#include <QSvgGenerator>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QPainter>


class classesvg{


public:
    classesvg();
    ~classesvg();

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

#endif // CLASSESVG_H
