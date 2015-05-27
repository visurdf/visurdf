#include "dessinateur.h"

Dessinateur::Dessinateur(VisuRDFAnalyseur * analyseur)
{
    this->analyseur = analyseur;
    //listeObjets = analyseur->getTousLesObjets();
    listeTypes = analyseur->getAllTypes(true);
    hauteurCase = 15;
    espacementVertical = 20;
    pourcentagePolice = 4.75;
}

Dessinateur::~Dessinateur()
{

}

float Dessinateur::calculLargeurColonne(Type * type, string nomPropriete){

    int largeur = nomPropriete.size();

    string nomType = type->getNom();
    set<Objet*> listeObjets = analyseur->getObjectByType(nomType, false);


    // On parcourt tous les objets du type
    for(set<Objet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++){

        Objet* objet = *it;



        ObjetRDF obj = objet->getProprietes();

        if(obj.size() != 0){



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

float Dessinateur::calculLargeurTableau(Type *type){

    float largeur = 0;
    list<string> proprietes = type->getProprietes();

    for(list<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++){

        string nomPropriete = *it;
        largeur = largeur + calculLargeurColonne(type, nomPropriete);

    }

    return largeur;
}

int Dessinateur::calculHauteurTableau(Type* type){
    int nbObjets = type->getNbObjet();

    int hauteur = nbObjets + 2;

    return (hauteur*hauteurCase);

}


int Dessinateur::calculHauteurDessin(){

    int hauteur = espacementVertical;
    for (set<Type*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
        Type* unType = *it;
        hauteur = hauteur + calculHauteurTableau(unType) + espacementVertical;

    }

    return hauteur;
}

// Dessine un tableau et le place aux coordonnées x, y
void Dessinateur::dessinTableau(Type *type, int x, int y, QPainter &painter){

    string nomType = type->getNom();

    // Dessin du nom du type

    QRect rectType(x, y, (nomType.size())*pourcentagePolice, hauteurCase);
    painter.drawRect(rectType);
    painter.drawText(rectType, Qt::AlignCenter, QString(nomType.c_str()));

    y = y + hauteurCase;

    // On dessine la première ligne
    list<string> proprietes = type->getProprietes();
    int xPropriete = x;
    for(list<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++){

        int yObjet = y;
        string nomPropriete = *it;
        float largeurBoite = this->calculLargeurColonne(type, nomPropriete);
        QRect rect(xPropriete,y,largeurBoite,hauteurCase);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter , QString(nomPropriete.c_str()));

        string nomType = type->getNom();
        set<Objet*> listeObjets = analyseur->getObjectByType(nomType, false);

        // On parcourt les objets du type pour dessiner les cases avec les valeurs de la propriete
        for(set<Objet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++){

            // On fait varier le placement vertical
            yObjet = yObjet + hauteurCase;
            Objet* objet = *it;

            ObjetRDF obj = objet->getProprietes();

            if(obj.size() != 0){

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


    void Dessinateur::dessinModeTableau(QPainter &painter){

        int x = 20;
        int y = 20;

        for(set<Type*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
            Type* type = *it;

            this->dessinTableau(type, x, y, painter);
            y = y + this->calculHauteurTableau(type) + espacementVertical ;
        }

    }

