#ifndef VISURDFDESSINATEUR_H
#define VISURDFDESSINATEUR_H
#include "visurdfobjet.h"
#include "visurdftype.h"
#include "visurdfanalyseur.h"
#include "visurdfboite.h"
#include "visurdfparametreur.h"
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


typedef map< string, VisuRDFBoite* > boiteObjet;

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
    float calculLargeurBoite(VisuRDFObjet* objet, float &largeurNom, float &largeurValeur);
    float calculHauteurBoite(VisuRDFObjet* objet);
    float calculLargeurType(VisuRDFType* type);
    void dessinBoite(VisuRDFObjet* objet, float x, float y, QPainter &painter, QBrush* brush);
    void dessinBoiteParType(VisuRDFType* type, float x, float y, QPainter &painter, QBrush* brush);
    void dessinModeBoite(QPainter& painter);
    void dessin(QPainter& painter);

    void dessinLiaison(VisuRDFObjet* objet1, VisuRDFObjet* objet2, QPainter&painter);
    void dessinToutesLiaisons(QPainter &painter);

    void dessinMap(QPainter &painter);

private :
   // list<Objet> listeObjets;
    set<VisuRDFType*> listeTypes;
    VisuRDFAnalyseur* analyseur;
    VisuRDFParametreur* parametreur;
    int hauteurCase;
    int espacementVertical;
    float pourcentagePolice;
    int pourcentagePoliceHauteur;
    int tailleMax;

    QFont f;
    QPen pen1;
    QPen pen2;
    QPen pen3;
    QBrush brush;

    boiteObjet mapBoiteObjet;
    boiteObjet mapBoiteType;
    map<int,QString> mapPolice;

};


#endif // VISURDFDESSINATEUR_H
