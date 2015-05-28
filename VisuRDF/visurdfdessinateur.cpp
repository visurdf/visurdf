#include "visurdfdessinateur.h"

VisuRDFDessinateur::VisuRDFDessinateur(VisuRDFAnalyseur * analyseur) {

    this->analyseur = analyseur;
    listeTypes = analyseur->getTousLesTypes(true);
    hauteurCase = 15;
    espacementVertical = 20;
    pourcentagePolice = 3.5;
    pourcentagePoliceHauteur = 10;
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

    // On parcourt tous les objets du type et on récupère le max de leur largeur
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

    // On retourne la largeur en nombre de pixel multiplié par un facteur en fonction de la police
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

    // On additionne les largeurs de chaque colonne
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

    // La hauteur est égale au nombre d'objets du type + 2 (1 ligne pour le nom des propriétés et 1 pour le nom du type)
    int nbObjets = type->getNbObjet();
    int hauteur = nbObjets + 2;

    // On multiplie par la hauteur des cases
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

    // Dessin du nom du type
    string nomType = type->getNom();
    QRect rectType(x, y, (nomType.size())*pourcentagePolice, hauteurCase);
    painter.drawRect(rectType);
    painter.drawText(rectType, Qt::AlignCenter, QString(nomType.c_str()));

    // Dessin de la première ligne
    y = y + hauteurCase;
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

        // Dessin des lignes représentant les objets
        for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

            // On fait varier le placement vertical
            yObjet = yObjet + hauteurCase;
            VisuRDFObjet* objet = *it;

            // On remplit la map(id, boite)
            int id = objet->getId();
            VisuRDFBoite* boite = new VisuRDFBoite(x, yObjet, calculLargeurTableau(type), hauteurCase);
            mapBoiteObjet->insert(std::make_pair(id, boite));

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

float VisuRDFDessinateur::calculLargeurBoite(VisuRDFObjet *objet){

    int largeurBoite = 0;

    ObjetRDF proprietes = objet->getProprietes();
    for(ObjetRDF::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomProp = (*it).first;
        list<string> valeurs = proprietes[nomProp];
        list<string>::iterator it2 = valeurs.begin();
        string valeur = *it2;
        string nomEtValeur = nomProp + " : " + valeur;

        int largeur = nomEtValeur.size();
        if (largeur > largeurBoite){
            largeurBoite = largeur;
        }

    }

    return (largeurBoite*pourcentagePolice);
}

int VisuRDFDessinateur::calculHauteurBoite(VisuRDFObjet *objet){

    int hauteur = 0;
    ObjetRDF proprietes = objet->getProprietes();

    for(ObjetRDF::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomProp = (*it).first;
        list<string> valeurs = proprietes[nomProp];
        list<string>::iterator it2 = valeurs.begin();
        string valeur = *it2;
        if (valeur != ""){
            hauteur = hauteur + 1;
        }

    }

    return (hauteur*pourcentagePoliceHauteur);
}

float VisuRDFDessinateur::calculLargeurType(VisuRDFType *type){
    float largeur = 0;

    string nomType = type->getNom();
    set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, true);

    // On parcourt tous les objets du type et on récupère le max de leur largeur
    for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

        VisuRDFObjet* objet = *it;

        float largeurObjet = calculLargeurBoite(objet);
        if (largeurObjet > largeur)
            largeur = largeurObjet;

    }

    return largeur;
}


void VisuRDFDessinateur::dessinBoite(VisuRDFObjet *objet, int x, int y, QPainter &painter){

    ObjetRDF proprietes = objet->getProprietes();
    float largeur = calculLargeurBoite(objet);
    float hauteur = calculHauteurBoite(objet);

    int yTexte = y + pourcentagePoliceHauteur/2;

    QRect rect(x,y,largeur,hauteur);
    painter.drawRect(rect);

    // On remplit la map(id, boite)
    int id = objet->getId();
    VisuRDFBoite* boite = new VisuRDFBoite(x, y, largeur, hauteur);
    mapBoiteObjet->insert(std::make_pair(id, boite));


    for(ObjetRDF::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomProp = (*it).first;
        list<string> valeurs = proprietes[nomProp];
        list<string>::iterator it2 = valeurs.begin();
        string valeur = *it2;

        if (valeur != ""){
        string nomEtValeur = nomProp + " : " + valeur;


        painter.drawText(x, yTexte, QString(nomEtValeur.c_str()));
        yTexte = yTexte + pourcentagePoliceHauteur;
       // painter.drawText(rect, Qt::AlignCenter , QString(nomEtValeur.c_str()));
        }

    }

}

void VisuRDFDessinateur::dessinBoiteParType(VisuRDFType *type, int x, int y, QPainter &painter){

    int yBoite = y;


    // On parcourt tous les objets du type

    string nomType = type->getNom();
    set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, true);

    // On parcourt tous les objets du type et on récupère le max de leur largeur
    for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

        VisuRDFObjet* objet = *it;

        dessinBoite(objet, x, yBoite, painter);

        yBoite = yBoite + calculHauteurBoite(objet) + espacementVertical;

    }

}

void VisuRDFDessinateur::dessinModeBoite(QPainter &painter){

    int x = 20;
    int y = 20;

    for(set<VisuRDFType*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
        VisuRDFType* type = *it;

        this->dessinBoiteParType(type, x, y, painter);
        x = x + calculLargeurType(type) + 20;

    }

}
