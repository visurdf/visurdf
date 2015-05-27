#include "dessinateur.h"

Dessinateur::Dessinateur(VisuRDFAnalyseur * analyseur)
{
    this->analyseur = analyseur;
    listeObjets = analyseur->getTousLesObjets();
    listeTypes = analyseur->getAllTypes(true);

}

Dessinateur::~Dessinateur()
{

}

int Dessinateur::calculLargeurColonne(Type * type, string nomPropriete){

    int largeur = nomPropriete.size();

    // On cherche tous les objets du type
    for(list<Objet>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++){

        Objet objet = *it;

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
    return (largeur*6);

}

int Dessinateur::calculLargeurTableau(Type *type){

    int largeur = 0;
    list<string> proprietes = type->getProprietes();

    for(list<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++){

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
void Dessinateur::dessinTableau(Type *type, int x, int y, QPainter &painter){

    //dessin des différents élements

    int hauteur = 12;

    // On dessine la première ligne
    list<string> proprietes = type->getProprietes();
    int xPropriete = x;
    for(list<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomPropriete = *it;
        int largeurBoite = this->calculLargeurColonne(type, nomPropriete);
        QRect rect(xPropriete,y,largeurBoite,hauteur);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter , QString(nomPropriete.c_str()));


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

                painter.drawRect(rectValeur);
                painter.drawText(rectValeur, Qt::AlignCenter, QString(valeur.c_str()));

            }

        }
        xPropriete = xPropriete + largeurBoite;

    }

}


void Dessinateur::dessinModeTableau(QPainter &painter){

    int x = 20;
    int y = 20;

     for(set<Type*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
         Type* type = *it;

         this->dessinTableau(type, x, y, painter);
         int hauteur = calculHauteurTableau(type);
         cout << "hauteur = " << hauteur << endl;
         y = y + (hauteur*12) + 20;
     }

}

