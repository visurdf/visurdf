#include "dessinateur.h"
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


Dessinateur::Dessinateur(VisuRDFAnalyseur * analyseur)
{
    listeObjets = analyseur->getTousLesObjets();
    listeTypes = analyseur->getTousLesTypes();
}

Dessinateur::~Dessinateur()
{

}

int Dessinateur::calculLargeurColonne(Type * type, string nomPropriete){

    int largeur = nomPropriete.size();

    // On cherche tous les objets du type
    for(list<Objet>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++){

        Objet objet = *it;

        // Comparaison types : redéfinir opérateur =
        // ?????????????????????????????????????
        if(objet.getType() == type){

            ObjetRDF::iterator iter = objet.getProprietes().find(nomPropriete);
            if(iter != objet.getProprietes().end()){
                list<string> valeurs = iter->second;

                list<string>::iterator it2 = valeurs.begin();
                string valeur = *it2;

                int largeurValeur = valeur.size();
                if (largeurValeur > largeur)
                    largeur = largeurValeur;

            }
        }

    }

    /////////////////// A FAIRE
    // A adapter en fonction de la largeur de la police
    return largeur;

}

int Dessinateur::calculLargeurTableau(Type *type){

    int largeur = 0;
    set<string> proprietes = type->getProprietes();

    for(set<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++){

        string nomPropriete = *it;
        largeur = largeur + calculLargeurColonne(type, nomPropriete);

    }

    return largeur;
}

int Dessinateur::calculHauteurTableau(Type* type){
    int nbObjets = type->getNbObjet();

    /////////////////// A FAIRE
    // A adapter en fonction de la hauteur de la police
    int hauteur = nbObjets + 1;

    return hauteur;

}

// Dessine un tableau et le place aux coordonnées x, y
void Dessinateur::dessinTableau(Type *type, int x, int y){

    int hauteur = 20;

    // On dessine la première ligne
    set<string> proprietes = type->getProprietes();
    int xPropriete = x;
    for(set<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomPropriete = *it;
        int largeurBoite = this->calculLargeurColonne(type, nomPropriete);
        QRect rect(xPropriete,y,largeurBoite,hauteur);
        painter1.drawRect(rect);
        painter1.drawText(xPropriete, y , QString(nomPropriete.c_str()));

     // On parcourt les objets du type pour dessiner les cases avec les valeurs de la propriete
        for(list<Objet>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++){

            // On fait varier le placement vertical
            y = y + 10;
            Objet objet = *it;

            if(objet.getType() == type){
                // On recupère la valeur de la propriété "nomPropriété"
                ObjetRDF::iterator iter = objet.getProprietes().find(nomPropriete);
                string valeur = "";
                if(iter != objet.getProprietes().end()){
                    list<string> valeurs = iter->second;

                    list<string>::iterator it2 = valeurs.begin();
                    valeur = *it2;
                }
                QRect rectValeur(xPropriete, y, largeurBoite, hauteur);
                painter1.drawRect(rectValeur);
                painter1.drawText(xPropriete, y, QString(valeur.c_str()));
            }

        }
        xPropriete = xPropriete + largeurBoite;

    }
}
