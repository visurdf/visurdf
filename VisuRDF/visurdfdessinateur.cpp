#include "visurdfdessinateur.h"

VisuRDFDessinateur::VisuRDFDessinateur(VisuRDFAnalyseur * analyseur) {

    this->analyseur = analyseur;

    parametreur = new VisuRDFParametreur();
    parametreur->lectureParametres();

    listeTypes = analyseur->getTousLesTypes(true);

    //Couleur du tableau
    QColor color; // = Qt::black;
    color.setRgb(14,50,200);
    pen3.setColor(color);

    //Couleur de la police
    QColor color2 = Qt::red;
    pen2.setColor(color2);

    //Couleur des liaisons
    pen1.setColor(Qt::black);

    //Déclaration de la police
    f = parametreur->getParamPolice();
    int fontSize = parametreur->getFontSize();
    f.setPixelSize(fontSize);

    //calcul des parametres d'affichage des boites en fonction de la taille de la police
    hauteurCase = 15/6*fontSize;
    espacementVertical = 20/6*fontSize;
    pourcentagePolice = 3.5/6*fontSize;
    pourcentagePoliceHauteur = 10/6*fontSize;


}


VisuRDFDessinateur::~VisuRDFDessinateur() {
    delete parametreur;

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



    painter.setPen(pen2);
    f.setBold(true);
    painter.setFont(f);
    // Dessin du nom du type
    string nomType = type->getNom();
    // QRect rectType(x, y, (nomType.size())*pourcentagePolice, hauteurCase);
    // painter.drawRect(rectType);
    painter.drawText(x, y + hauteurCase/2, QString(nomType.c_str()));
    //  painter.drawText(rectType, Qt::AlignCenter, QString(nomType.c_str()));

    f.setBold(false);
    painter.setPen(pen1);
    painter.setFont(f);
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
        QBrush brush = Qt::gray;
        painter.fillRect(rect, brush);
        painter.drawText(rect, Qt::AlignCenter , QString(nomPropriete.c_str()));

        string nomType = type->getNom();
        set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, false);


        // Dessin des lignes représentant les objets
        for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

            // On fait varier le placement vertical
            yObjet = yObjet + hauteurCase;
            VisuRDFObjet* objet = *it;

            // On remplit la map(id, boite)
            //   int id = objet->getId();
            VisuRDFBoite* boite = new VisuRDFBoite(x, yObjet, calculLargeurTableau(type), hauteurCase);
            mapBoiteObjet.insert(std::make_pair(objet->getNom(), boite));
            cout << "objet : " << objet->getNom() << endl;
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
        //x = x + 50;
        y = y + this->calculHauteurTableau(type) + espacementVertical ;
    }


}

/*float VisuRDFDessinateur::calculLargeurBoite(VisuRDFObjet *objet){

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
}*/

float VisuRDFDessinateur::calculLargeurBoite(VisuRDFObjet *objet, float &largeurNom, float &largeurValeur){

    largeurNom =0;
    largeurValeur = 0;
    ObjetRDF proprietes = objet->getProprietes();
    for(ObjetRDF::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomProp = (*it).first;
        list<string> valeurs = proprietes[nomProp];
        list<string>::iterator it2 = valeurs.begin();
        string valeur = *it2;
        string nomAffiche = nomProp + " : ";
        int largeur1 = nomAffiche.size();
        if (largeur1 > largeurNom){
            largeurNom = largeur1;
        }
        int largeur2 = valeur.size();
        if (largeur2 > largeurValeur){
            largeurValeur = largeur2;
        }

    }
    largeurNom = largeurNom*pourcentagePolice;
    largeurValeur = largeurValeur*pourcentagePolice;

    return (largeurNom+largeurValeur);
}

float VisuRDFDessinateur::calculHauteurBoite(VisuRDFObjet *objet){

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

    return ((hauteur-1)*pourcentagePoliceHauteur);
}

float VisuRDFDessinateur::calculLargeurType(VisuRDFType *type){
    float largeur = 0;

    string nomType = type->getNom();
    set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, true);

    // On parcourt tous les objets du type et on récupère le max de leur largeur
    for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

        VisuRDFObjet* objet = *it;
        float lN;
        float lV;
        float largeurObjet = calculLargeurBoite(objet, lN, lV);
        if (largeurObjet > largeur)
            largeur = largeurObjet;

    }

    return largeur;
}


void VisuRDFDessinateur::dessinBoite(VisuRDFObjet *objet, float x, float y, QPainter &painter){

    float largeurNom;
    float largeurValeur;
    ObjetRDF proprietes = objet->getProprietes();
    float largeur = calculLargeurBoite(objet,largeurNom, largeurValeur);
    float hauteur = calculHauteurBoite(objet);

    float yTexte = y + pourcentagePoliceHauteur/2;
    painter.setPen(pen1);
    QRect rect(x,y,largeur,hauteur);
    painter.drawRoundedRect(rect,3,3);

    QLine lineType(x,y+pourcentagePoliceHauteur,x+largeur,y+pourcentagePoliceHauteur);
    painter.drawLine(lineType);
   // QRect rectType(x,y,largeur,pourcentagePoliceHauteur);
    //painter.drawRect(rectType);
    // On remplit la map(objet, boite)
    VisuRDFBoite* boite = new VisuRDFBoite(x, y, largeur, hauteur);
    mapBoiteObjet.insert(std::make_pair(objet->getNom(), boite));
    cout << "objet : " << objet->getNom() << endl;



    list<string> listeNom;
    for(ObjetRDF::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomProp = (*it).first;
        listeNom.push_front(nomProp);

    }


    for(list<string>::iterator iter = listeNom.begin(); iter!=listeNom.end(); iter++){
        string nom = *iter;
        list<string> valeurs = proprietes[nom];
        list<string>::iterator it2 = valeurs.begin();
        string valeur = *it2;

        if(valeur!=""){

            if(nom == "type"){
                string valeurType = valeur;
                painter.setPen(pen2);
                f.setBold(true);
                painter.setFont(f);
                painter.drawText(x, yTexte, QString(valeurType.c_str()));
                //yTexte = yTexte + pourcentagePoliceHauteur;
            }

            else if(nom == "name"){
                string valeurName = valeur;
                painter.setPen(pen2);
                f.setBold(true);
                painter.setFont(f);
                painter.drawText(x+largeurNom, yTexte, QString(valeurName.c_str()));
                yTexte = yTexte + pourcentagePoliceHauteur;

            }

            if((nom!="type")&(nom!="name")){
                string nomAffiche = nom + " : ";

                painter.setPen(pen1);
                f.setBold(true);
                painter.setFont(f);
                painter.drawText(x, yTexte, QString(nomAffiche.c_str()));

               // painter.setPen(pen1);
                f.setBold(false);
                painter.setFont(f);
                painter.drawText(x+largeurNom, yTexte, QString(valeur.c_str()));
                yTexte = yTexte + pourcentagePoliceHauteur;
            }
        }

    }





}

void VisuRDFDessinateur::dessinBoiteParType(VisuRDFType *type, float x, float y, QPainter &painter){

    float yBoite = y;


    // On parcourt tous les objets du type

    string nomType = type->getNom();
    set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, true);

    // On parcourt tous les objets du type
    for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

        VisuRDFObjet* objet = *it;

        dessinBoite(objet, x, yBoite, painter);

        yBoite = yBoite + calculHauteurBoite(objet) + espacementVertical;

    }

}

void VisuRDFDessinateur::dessinModeBoite(QPainter &painter){

    float x = 20;
    float y = 20;

    for(set<VisuRDFType*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
        VisuRDFType* type = *it;

        this->dessinBoiteParType(type, x, y, painter);
        x = x + calculLargeurType(type) + 20;

    }


}

void VisuRDFDessinateur::dessinLiaison(VisuRDFObjet *objet1, VisuRDFObjet *objet2, QPainter &painter){

    string name1 = objet1->getNom();
    string name2 = objet2->getNom();
    VisuRDFBoite* boite1 = mapBoiteObjet[name1];
    VisuRDFBoite* boite2 = mapBoiteObjet[name2];
    float x1 = boite1->getX();
    float x2 = boite2->getX();
    float y1 = boite1->getY();
    float y2 = boite2->getY();
    float largeur1 = boite1->getLargeur();
    float largeur2 = boite2->getLargeur();
    float hauteur1 = boite1->getHauteur();
    float hauteur2 = boite2->getHauteur();

    // Si l'objet 2 est à droite de l'objet 1
    if(x2>(x1+largeur1)){

        QLine line(x1+largeur1,y1+hauteur1/2, x2, y2+hauteur2/2);
        painter.drawLine(line);
    }

    // Si l'objet 2 est à gauche de l'objet 1
    else if((x2+largeur2)<x1){
        QLine line(x2+largeur2,y2+hauteur2/2, x1, y1+hauteur1/2);
        painter.drawLine(line);
    }

    // Si ils sont sur la même verticale
    else{
        // Si l'objet 2 est sous l'objet 1
        if(y2>y1){
            QLine line(x1+largeur1/2, y1+hauteur1, x2 + largeur2/2, y2);
            painter.drawLine(line);
        }

        // si l'objet 2 est au dessus de l'objet 1
        else{
            QLine line(x1+largeur1/2, y1, x2 + largeur2/2, y2+hauteur2);
            painter.drawLine(line);
        }

    }


}

void VisuRDFDessinateur::dessinToutesLiaisons(QPainter &painter){

    painter.setPen(pen3);

    map<VisuRDFObjet*, list<VisuRDFObjet*> > mapRelations = analyseur->getRelations();
    for(map<VisuRDFObjet*, list<VisuRDFObjet*> >::iterator iter = mapRelations.begin(); iter!= mapRelations.end(); iter++){
        VisuRDFObjet* objet1 = (*iter).first;
        list<VisuRDFObjet*> objets = mapRelations[objet1];
        for(list<VisuRDFObjet*>::iterator it2 = objets.begin(); it2!= objets.end(); it2++){
            VisuRDFObjet* objet2 = *it2;
          //  cout << "objet 1 : " << objet1->getNom() << endl;
           // cout << "objet 2 : " << objet2->getNom() << endl;
            dessinLiaison(objet1,objet2, painter);
        }


    }
    cout << "fin "<< endl;
}
