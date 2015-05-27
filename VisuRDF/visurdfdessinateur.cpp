#include "visurdfdessinateur.h"

VisuRDFDessinateur::VisuRDFDessinateur(VisuRDFAnalyseur * analyseur) {

    this->analyseur = analyseur;
    //listeObjets = analyseur->getTousLesObjets();
    listeTypes = analyseur->getTousLesTypes(true);
    hauteurCase = 15;
    espacementVertical = 20;
    pourcentagePolice = 4.75;
}


VisuRDFDessinateur::~VisuRDFDessinateur() {

}


/**
 * @brief Dessinateur::calculLargeurColonne
 * @param type
 * @param nomPropriete
 * @return largeur de la colonne
 */

float VisuRDFDessinateur::calculLargeurColonne(VisuRDFType * type, string nomPropriete) {

    int largeur = nomPropriete.size();

    string nomType = type->getNom();
    set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, false);

    // On parcourt tous les objets du type
    for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

        VisuRDFObjet* objet = *it;

        ObjetRDF obj = objet->getProprietes();

        if(obj.size() != 0) {

            list<string> valeurs = obj[nomPropriete];

            list<string>::iterator it2 = valeurs.begin();
            string valeur = *it2;

            int largeurValeur = valeur.size();
            if (largeurValeur > largeur)
                largeur = largeurValeur;
        }
    }

    // A adapter en fonction de la largeur de la police
    return (largeur*pourcentagePolice);
}


/**
 * @brief Dessinateur::calculLargeurTableau
 * @param type
 * @return largeur du tableau
 */

float VisuRDFDessinateur::calculLargeurTableau(VisuRDFType *type) {

    float largeur = 0;
    list<string> proprietes = type->getProprietes();

    for(list<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++) {
        string nomPropriete = *it;
        largeur = largeur + calculLargeurColonne(type, nomPropriete);
    }

    return largeur;
}


/**
 * @brief Dessinateur::calculHauteurTableau
 * @param type
 * @return hauteur du tableau
 */

int VisuRDFDessinateur::calculHauteurTableau(VisuRDFType* type) {

    int nbObjets = type->getNbObjet();
    int hauteur = nbObjets + 2;

    return (hauteur*hauteurCase);
}


/**
 * @brief Dessinateur::calculHauteurDessin
 * @return hauteur du dessin
 */

int VisuRDFDessinateur::calculHauteurDessin() {

    int hauteur = espacementVertical;
    for (set<VisuRDFType*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
        VisuRDFType* unType = *it;
        hauteur = hauteur + calculHauteurTableau(unType) + espacementVertical;
    }

    return hauteur;
}


/**
 * @brief Dessinateur::dessinTableau, dessine un tableau et le place aux coordonnées (x,y)
 * @param type
 * @param x
 * @param y
 * @param painter
 */

void VisuRDFDessinateur::dessinTableau(VisuRDFType *type, int x, int y, QPainter &painter) {

    string nomType = type->getNom();

    // Dessin du nom du type
    QRect rectType(x, y, (nomType.size())*pourcentagePolice, hauteurCase);
    painter.drawRect(rectType);
    painter.drawText(rectType, Qt::AlignCenter, QString(nomType.c_str()));

    y = y + hauteurCase;

    // On dessine la première ligne
    list<string> proprietes = type->getProprietes();
    int xPropriete = x;
    for(list<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++) {

        int yObjet = y;
        string nomPropriete = *it;
        float largeurBoite = this->calculLargeurColonne(type, nomPropriete);
        QRect rect(xPropriete,y,largeurBoite,hauteurCase);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter , QString(nomPropriete.c_str()));

        string nomType = type->getNom();
        set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, false);

        // On parcourt les objets du type pour dessiner les cases avec les valeurs de la propriete
        for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

            // On fait varier le placement vertical
            yObjet = yObjet + hauteurCase;
            VisuRDFObjet* objet = *it;

            ObjetRDF obj = objet->getProprietes();

            if(obj.size() != 0) {

                string valeur = "";
                // On recupère la valeur de la propriété "nomPropriété"
                ObjetRDF obj = objet->getProprietes();
                if(obj.size() != 0){
                    list<string> valeurs = obj[nomPropriete];

                    list<string>::iterator it2 = valeurs.begin();
                    valeur = *it2;
                }
                QRect rectValeur(xPropriete, yObjet, largeurBoite, hauteurCase);

                painter.drawRect(rectValeur);
                painter.drawText(rectValeur, Qt::AlignCenter, QString(valeur.c_str()));
            }
        }
        xPropriete = xPropriete + largeurBoite;
    }
}


/**
 * @brief Dessinateur::dessinModeTableau
 * @param painter
 */

void VisuRDFDessinateur::dessinModeTableau(QPainter &painter){

    int x = 20;
    int y = 20;

    for(set<VisuRDFType*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
        VisuRDFType* type = *it;

        this->dessinTableau(type, x, y, painter);
        y = y + this->calculHauteurTableau(type) + espacementVertical ;
    }
}

