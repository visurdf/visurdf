#ifndef DESSINATEUR_H
#define DESSINATEUR_H
#include "objet.h"
#include "type.h"
#include "visurdfanalyseur.h"
#include "string"
#include <QPainter>
#include <QSvgRenderer>
#include <QSvgGenerator>
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
    void dessinTableau(Type *type, int x, int y);

private :
    list<Objet> listeObjets;
    list<Type> listeTypes;
    VisuRDFAnalyseur * analyseur;
    QPainter painter1;

};


#endif // DESSINATEUR_H
