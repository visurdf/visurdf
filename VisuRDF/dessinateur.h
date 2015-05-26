#ifndef DESSINATEUR_H
#define DESSINATEUR_H
#include "objet.h"
#include "type.h"
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



class Dessinateur
{
public:
    Dessinateur(VisuRDFAnalyseur * analyseur);
    ~Dessinateur();
    int calculLargeurColonne(Type* type, string nomPropriete);
    int calculLargeurTableau(Type* type);
    int calculHauteurTableau(Type *type);
    void dessinTableau(Type *type, int x, int y, QPainter &painter);
    void dessinModeTableau(QPainter& painter);


private :
    list<Objet> listeObjets;
    set<Type*> listeTypes;
    VisuRDFAnalyseur * analyseur;

};


#endif // DESSINATEUR_H
