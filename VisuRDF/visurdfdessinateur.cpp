#include "visurdfdessinateur.h"

VisuRDFDessinateur::VisuRDFDessinateur(VisuRDFAnalyseur * analyseur) {

    this->analyseur = analyseur;
    isFirst = true;

    parametreur = new VisuRDFParametreur();
    parametreur->lectureParametres();

    listeTypes = analyseur->getTousLesTypes(true);

    // Pen 3 : Couleur des liaisons
    QColor color; // = Qt::black;
    color.setRgb(14,50,200);
    pen3.setColor(color);

    //Pen 2 : Couleur de la police du type
    if(parametreur->getParamMode()=="boite" && parametreur->getParamColoration()==1){
        pen2.setColor(Qt::black);
    }
    else{
        QColor color2 = Qt::red;
        pen2.setColor(color2);
    }

    //Pen 1 : Couleur du tableau et de la police des propriétés
    pen1.setColor(Qt::black);

    //Déclaration de la police
    f = parametreur->getParamPolice();

    // Déclaration taille police
    if(parametreur->getFontSize()!=0){
        fontSize = parametreur->getFontSize();
    }
    else fontSize = 8;  // Paramètre par défaut
    f.setPixelSize(fontSize);

    // Déclaration pourcentages police et taille Max
    if(parametreur->getPourcentagePolice()!=0){
        pourcentagePolice = (parametreur->getPourcentagePolice())*fontSize;
    }
    else pourcentagePolice = 0.7*fontSize;

    if(parametreur->getPourcentagePoliceHauteur()!=0){
        pourcentagePoliceHauteur = (parametreur->getPourcentagePoliceHauteur())*fontSize;
    }
    else pourcentagePoliceHauteur = 1.2*fontSize;

    if(parametreur->getTailleMax()!=0){
        tailleMax = parametreur->getTailleMax();
    }
    else tailleMax = 50;

    // Calcul des parametres d'affichage des boites en fonction de la taille de la police
    hauteurCase = pourcentagePoliceHauteur * 2;
    // hauteurCase = 15/5.5*fontSize;
    espacementVertical = 20/5.5*fontSize;

    // Déclaration mode couleur ou non
    if(parametreur->getParamColoration()==1){
        couleur = 1;
    }
    else{
        couleur = 0;
    }

    // Déclaration du mode (tableau ou boite)
    if(parametreur->getParamMode()=="boite"){
        mode = "boite";
    }
    else{
        mode = "tableau";
    }

}


VisuRDFDessinateur::~VisuRDFDessinateur() {
    delete parametreur;

}

/**
 * @brief VisuRDFDessinateur::getParametreur
 * @return le parametreur
 */
VisuRDFParametreur* VisuRDFDessinateur::getParametreur(){
    return parametreur;
}

/**
 * @brief VisuRDFDessinateur::setFont, met à jour la police
 * @param font
 */
void VisuRDFDessinateur::setFont(QFont font){
    f = font;
}

/**
 * @brief VisuRDFDessinateur::setFontSize, met à jour la taille de la police
 * @param size
 */
void VisuRDFDessinateur::setFontSize(int size){

    float ancienPourcentage = pourcentagePolice;
    float ancienPourcentageH = pourcentagePoliceHauteur;
    // On calcule les nouveaux coefficients de pourcentage
    pourcentagePolice = pourcentagePolice/fontSize*size;
    pourcentagePoliceHauteur = pourcentagePoliceHauteur/fontSize*size;
    hauteurCase = pourcentagePoliceHauteur * 2;
    // On modifie la taille de la police actuelle
    fontSize = size;
    f.setPixelSize(size);

    // On met à jour les informations des boites (actualisées avec la nouvelle taille de police)
    for (boiteObjet::iterator it = mapBoiteObjet.begin(); it!=mapBoiteObjet.end(); it++){
        string nomObjet = (*it).first;
        VisuRDFBoite* boite = mapBoiteObjet[nomObjet];
        boite->setX(boite->getX()*pourcentagePolice/ancienPourcentage);
        boite->setY(boite->getY()*pourcentagePoliceHauteur/ancienPourcentageH);
        boite->setHauteur(boite->getHauteur()*pourcentagePoliceHauteur/ancienPourcentageH);
        boite->setLargeur(boite->getLargeur()*pourcentagePolice/ancienPourcentage);
    }

    for(boiteObjet::iterator it2 = mapBoiteType.begin(); it2!= mapBoiteType.end(); it2++){
        string nomType = (*it2).first;
        VisuRDFType* type = analyseur->getTypeParNom(nomType,true);
        VisuRDFBoite* boite = mapBoiteType[nomType];
        boite->setX(boite->getX()*pourcentagePolice/ancienPourcentage);
        boite->setY(boite->getY()*pourcentagePoliceHauteur/ancienPourcentageH);
        boite->setLargeur(calculLargeurTableau(type));
        boite->setHauteur(calculHauteurTableau(type));
    }


}

/**
 * @brief VisuRDFDessinateur::setPourcentagePolice
 * @param pourcentage
 */
void VisuRDFDessinateur::setPourcentagePolice(float pourcentage){

    float ancienPourcentage = pourcentagePolice;
    pourcentagePolice = pourcentage*fontSize;


    // On met à jour les informations des boites (actualisées avec les nouveaux coefficients)
    for (boiteObjet::iterator it = mapBoiteObjet.begin(); it!=mapBoiteObjet.end(); it++){
        string nomObjet = (*it).first;
        VisuRDFBoite* boite = mapBoiteObjet[nomObjet];
        boite->setX(boite->getX()*pourcentagePolice/ancienPourcentage);
        boite->setLargeur(boite->getLargeur()*pourcentagePolice/ancienPourcentage);
    }

    for(boiteObjet::iterator it2 = mapBoiteType.begin(); it2!= mapBoiteType.end(); it2++){
        string nomType = (*it2).first;
        VisuRDFType* type = analyseur->getTypeParNom(nomType,true);
        VisuRDFBoite* boite = mapBoiteType[nomType];
        boite->setX(boite->getX()*pourcentagePolice/ancienPourcentage);
        boite->setLargeur(calculLargeurTableau(type));
    }


}

/**
 * @brief VisuRDFDessinateur::setPourcentagePoliceHauteur
 * @param pourcentage
 */
void VisuRDFDessinateur::setPourcentagePoliceHauteur(float pourcentage){

    float ancienPourcentage = pourcentagePoliceHauteur;
    pourcentagePoliceHauteur = pourcentage*fontSize;
    hauteurCase = pourcentagePoliceHauteur * 2;

    // On met à jour les informations des boites (actualisées avec les nouveaux coefficients)
    for (boiteObjet::iterator it = mapBoiteObjet.begin(); it!=mapBoiteObjet.end(); it++){
        string nomObjet = (*it).first;
        VisuRDFBoite* boite = mapBoiteObjet[nomObjet];
        boite->setY(boite->getY()*pourcentagePoliceHauteur/ancienPourcentage);
        boite->setHauteur(boite->getHauteur()*pourcentagePoliceHauteur/ancienPourcentage);
    }

    for(boiteObjet::iterator it2 = mapBoiteType.begin(); it2!= mapBoiteType.end(); it2++){
        string nomType = (*it2).first;
        VisuRDFType* type = analyseur->getTypeParNom(nomType,true);
        VisuRDFBoite* boite = mapBoiteType[nomType];
        boite->setY(boite->getY()*pourcentagePoliceHauteur/ancienPourcentage);
        boite->setHauteur(calculHauteurTableau(type));
    }




}

/**
 * @brief VisuRDFDessinateur::setTailleMax
 * @param taille
 */
void VisuRDFDessinateur::setTailleMax(float taille){
    tailleMax = taille;
}

/**
 * @brief VisuRDFDessinateur::setCouleur, modifie le mode (coloré ou non coloré)
 * @param isCouleur
 */
void VisuRDFDessinateur::setCouleur(int isCouleur){
    couleur = isCouleur;
    cout << "couleur : " << couleur << endl;

    // On actualise les couleurs des boites
    // if(mode=="boite"){
    int i=0;
    for(set<VisuRDFType*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
        VisuRDFType* type = *it;
        string nomType = type->getNom();
        set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, true);


        QBrush* brush = new QBrush();

        if(couleur==1){
            map<int,QBrush*> mapBrush = parametreur->getListePinceau();
            brush = mapBrush[i];
        }

        for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

            VisuRDFObjet* objet = *it;
            string nomObjet = objet->getNom();


            mapBoiteObjet[nomObjet]->setBrush(brush);
        }

        i++;
    }

    if(mode=="boite" && couleur==1){
        pen2.setColor(Qt::black);
    }
    else{
        QColor color2 = Qt::red;
        pen2.setColor(color2);
    }

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

            int largeurValeur = tailleMax;
            if(valeur.size()<tailleMax){
                largeurValeur = valeur.size();
            }
            if (largeurValeur > largeur)
                largeur = largeurValeur;
        }
    }

    // On retourne la largeur en nombre de pixel multiplié par un facteur en fonction de la police
    return (largeur*pourcentagePolice);
}

void VisuRDFDessinateur::setMode(string new_mode){
    mode = new_mode;
    if(mode=="boite" && couleur==1){
        pen2.setColor(Qt::black);
    }
    else{
        pen2.setColor(Qt::red);
    }
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

float VisuRDFDessinateur::calculHauteurTableau(VisuRDFType* type) {


    // On initialise hauteur
    float hauteur = 2*hauteurCase;
    set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(type->getNom(), false);

    for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

        VisuRDFObjet* obj = *it;
        string nomObjet = obj->getNom();
        hauteur = hauteur + mapBoiteObjet[nomObjet]->getHauteur();

    }

    return hauteur;


}

/**
 * @brief VisuRDFDessinateur::remplissageTableau, permet de remplir les mapBoiteObjet et mapBoiteType avant le premier dessin
 * @param type
 * @param x
 * @param y
 */
void VisuRDFDessinateur::remplissageTableau(VisuRDFType *type, int x, int y){


    // On calcule la largeur du tableau et on initialise la hauteur du tableau avec 1 ligne pour chaque objet
    float largeurTableau = calculLargeurTableau(type);
    float hauteurTableau = (type->getNbObjet()+2)*hauteurCase;
    string nomType = type->getNom();

    //On remplit la map "type / boite"
    VisuRDFBoite* boiteTableau = new VisuRDFBoite(x, y, largeurTableau, hauteurTableau);
    mapBoiteType[nomType]=boiteTableau;

    // On écrira le nom du Type en y, on décale donc le y pour la première ligne
    y = y + hauteurCase;
    // On parcourt colonne par colonne pour mettre à jour les boites objets
    list<string> proprietes = type->getProprietes();
    for(list<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++) {


        int yObjet = y;
        string nomPropriete = *it;

        // On parcourt la liste des objets du type, et on va récupérer la valeur correspondant à nomPropriete

        set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, false);

        for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

            // On fait varier le placement vertical
            yObjet = yObjet + hauteurCase;

            VisuRDFObjet* objet = *it;
            string valeur = "";
            ObjetRDF obj = objet->getProprietes();

            // On calcule la taille de la valeur pour savoir combien de lignes elle prendra
            if(obj.size() != 0){
                list<string> valeurs = obj[nomPropriete];
                list<string>::iterator it2 = valeurs.begin();
                valeur = *it2;
            }
            int nbLignes = 1;
            if(valeur.size()>tailleMax){
                nbLignes = valeur.size()/tailleMax +1 ;
            }

            // On met à jour la mapBoiteObjet si elle existe déjà
            if(mapBoiteObjet[objet->getNom()]!=NULL){

                mapBoiteObjet[objet->getNom()]->setY(yObjet);
                mapBoiteObjet[objet->getNom()]->setX(x);
                mapBoiteObjet[objet->getNom()]->setLargeur(calculLargeurTableau(type));
                // On vérifie si la boite n'était pas déjà plus grande que cette propriété
                // Si elle est la nouvelle boite la plus grande, on met à jour la hauteur de la boite
                if(mapBoiteObjet[objet->getNom()]->getHauteur()<hauteurCase*nbLignes||nomPropriete=="name"){
                    mapBoiteObjet[objet->getNom()]->setHauteur(hauteurCase*nbLignes);
                    yObjet = yObjet + (nbLignes-1)*hauteurCase;
                }
                // Sinon, on met yObjet sur la bonne ligne
                else{
                    float hauteur = mapBoiteObjet[objet->getNom()]->getHauteur();
                    yObjet = yObjet + hauteur - hauteurCase;
                }

            }
            // Si mapBoiteObjet n'existe pas, on remplit la map
            else{
                VisuRDFBoite* boite = new VisuRDFBoite(x, yObjet, calculLargeurTableau(type), hauteurCase*nbLignes);
                mapBoiteObjet[objet->getNom()]=boite;
                yObjet = yObjet + (nbLignes-1)*hauteurCase;
            }

        }

    }

    // On met à jour la hauteur du tableau dans mapBoiteType
    mapBoiteType[nomType]->setHauteur(calculHauteurTableau(type));

}


/**
 * @brief Dessinateur::dessinTableau, dessine un tableau et le place aux coordonnées (x,y)
 * @param type
 * @param x
 * @param y
 * @param painter
 */

void VisuRDFDessinateur::dessinTableau(VisuRDFType *type, int x, int y, QPainter &painter) {

    // On prend le pen du tableau
    painter.setPen(pen2);
    f.setBold(true);
    painter.setFont(f);

    string nomType = type->getNom();

    // Dessin du nom du type

    painter.drawText(x, y + hauteurCase/2, QString(nomType.c_str()));

    f.setBold(false);
    painter.setPen(pen1);
    painter.setFont(f);
    // On dessine colonne par colonne
    y = y + hauteurCase;
    list<string> proprietes = type->getProprietes();
    int xPropriete = x;
    for(list<string>::iterator it = proprietes.begin(); it!= proprietes.end(); it++) {

        // On dessine en premier le nom de la propriété (première ligne)

        string nomPropriete = *it;
        float largeurBoite = this->calculLargeurColonne(type, nomPropriete);
        QRect rect(xPropriete,y,largeurBoite,hauteurCase);

        QBrush brush = Qt::gray;
        painter.fillRect(rect, brush);
        painter.drawRect(rect);
        // On remplace la propriété "name" par "id"
        if(nomPropriete == "name"){
            painter.drawText(rect, Qt::AlignCenter , "id");
        }
        else{
            painter.drawText(rect, Qt::AlignCenter , QString(nomPropriete.c_str()));
        }

        // On utilise la map des objets pour dessiner (on prend uniquement les objets du type donné)

        for(boiteObjet::iterator itBoite = mapBoiteObjet.begin(); itBoite!= mapBoiteObjet.end(); itBoite++){

            string nomObjet = (*itBoite).first;
            VisuRDFBoite* boite = mapBoiteObjet[nomObjet];
            VisuRDFObjet* objet = analyseur->getObjetparNom(nomObjet);

            if(objet->getType()->getNom()==nomType){

                string valeur = "";
                // On recupère la valeur de la propriété "nomPropriété"
                ObjetRDF obj = objet->getProprietes();
                if(obj.size() != 0){
                    list<string> valeurs = obj[nomPropriete];
                    list<string>::iterator it2 = valeurs.begin();
                    valeur = *it2;
                }
                QRect rectValeur(xPropriete, boite->getY(), largeurBoite, boite->getHauteur());
                painter.drawRect(rectValeur);


                // Si la valeur est inférieure à la taille max, on l'affiche sur une ligne
                if(valeur.size()<=tailleMax){
                    painter.drawText(rectValeur, Qt::AlignCenter, QString(valeur.c_str()));
                }

                // Sinon on l'affiche sur plusieurs lignes
                else{
                    // Calcul de nbLignes à revoir (dépend de la taille des mots...)
                    int nbLignes = valeur.size()/tailleMax +1 ;
                    int pos = 0;
                    int posEspace = 0;
                    int precPos = 0;

                    for(int i =0; i< nbLignes; i++){

                        // Si il n'y a aucun espace dans le string
                        if((int)valeur.find(" ",0)==-1){
                            string valeurTronquee = valeur.substr(i*tailleMax,tailleMax);
                            QRect rectProp(xPropriete,boite->getY()+i*hauteurCase,largeurBoite,hauteurCase);
                            painter.drawText(rectProp, Qt::AlignCenter,QString(valeurTronquee.c_str()));

                        }

                        else{
                            // On met le curseur sur le précédent espace
                            pos = posEspace;
                            int taille = 0;

                            // On cherche le prochain espace pour lequel la suite de mots ne dépasse pas tailleMax
                            while((taille<tailleMax)&(pos!=-1)){
                                posEspace = pos;
                                pos = valeur.find(" ", posEspace+1);
                                taille = pos - precPos;
                            }

                            // On récupère la chaîne à afficher
                            string valeur2;
                            if(i!=nbLignes-1){
                                valeur2 = valeur.substr(precPos,(posEspace-precPos));
                            }

                            else
                                valeur2=valeur.substr(precPos);

                            precPos = posEspace;
                            //On affiche la chaine et on fait varier le y
                            QRect rectProp(xPropriete,boite->getY()+i*hauteurCase,largeurBoite,hauteurCase);
                            painter.drawText(rectProp, Qt::AlignCenter,QString(valeur2.c_str()));

                        }

                    }
                }


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

        // Si on n'a pas encore dessiné les tableaux, on remplit les maps ("objet,boite" et "type,boite") via la fonction remplissageTableau
        if(isFirst){
            this->remplissageTableau(type,x,y);
        }

        this->dessinTableau(type, x, y, painter);
        //x = x + 50;
        y = y + this->calculHauteurTableau(type) + espacementVertical ;
    }


    isFirst = false;
}

/**
 * @brief VisuRDFDessinateur::calculLargeurBoite, calcule la largeur de la boite et renvoie également par référence
 * la largeur du nom de propriété (partie gauche de la boite) et la largeur de la valeur de la propriété (partie droite)
 * @param objet
 * @param largeurNom (passage par référence)
 * @param largeurValeur (passage par référence)
 * @return largeur de la boite
 */
float VisuRDFDessinateur::calculLargeurBoite(VisuRDFObjet *objet, float &largeurNom, float &largeurValeur){

    largeurNom =0;
    largeurValeur = 0;
    ObjetRDF proprietes = objet->getProprietes();
    // On parcourt la liste des propriétés de l'objet
    for(ObjetRDF::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomProp = (*it).first;

        list<string> valeurs = proprietes[nomProp];
        list<string>::iterator it2 = valeurs.begin();
        string valeur = *it2;

        string nomAffiche = nomProp + " : ";
        int largeur1 = 0;
        int largeur2 = 0;
        if(nomProp == "type"){
            largeur1 = valeur.size();
            largeur2 = 0;
        }
        else{
            largeur1 = nomAffiche.size();
            largeur2 = valeur.size();
        }

        // La largeur doit être inférieure ou égale à la taille max
        if(largeur2>tailleMax)
            largeur2 = tailleMax;

        // Mise à jour largeur nom si besoin
        if (largeur1 > largeurNom){
            largeurNom = largeur1;
        }


        // Mise à jour largeur valeur si besoin
        if (largeur2 > largeurValeur){

            largeurValeur = largeur2;
        }

    }

    largeurNom = largeurNom*pourcentagePolice;
    largeurValeur = largeurValeur*pourcentagePolice;

    return (largeurNom+largeurValeur);
}

/**
 * @brief VisuRDFDessinateur::calculHauteurBoite
 * @param objet
 * @return hauteur de la boite
 */
float VisuRDFDessinateur::calculHauteurBoite(VisuRDFObjet *objet){

    int hauteur = 0;
    ObjetRDF proprietes = objet->getProprietes();
    for(ObjetRDF::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomProp = (*it).first;
        list<string> valeurs = proprietes[nomProp];
        list<string>::iterator it2 = valeurs.begin();
        string valeur = *it2;
        if ((valeur != "")&(nomProp!="type")&(nomProp!="name")){
            int size = valeur.size();
            // Si l'affichage est sur plusieurs lignes
            if(size > tailleMax){
                hauteur = hauteur + size/tailleMax +1;
            }
            else{
                hauteur = hauteur + 1;
            }
        }

    }

    return ((hauteur+1)*pourcentagePoliceHauteur);
}

/**
 * @brief VisuRDFDessinateur::calculLargeurType
 * @param type
 * @return largeur de boite pour l'objet du type donné (correspond à la plus grande largeur de boite du type donné)
 */
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

/**
 * @brief VisuRDFDessinateur::dessinBoite, dessine une boite aux coordonnées x,y, et de couleur associée à brush
 * @param objet
 * @param x
 * @param y
 * @param painter
 * @param brush
 */
void VisuRDFDessinateur::dessinBoite(VisuRDFObjet *objet, float x, float y, QPainter &painter, QBrush* brush){

    float largeurNom;
    float largeurValeur;
    ObjetRDF proprietes = objet->getProprietes();
    float largeur = calculLargeurBoite(objet,largeurNom, largeurValeur);
    float largeurType = calculLargeurType(objet->getType());
    float hauteur = calculHauteurBoite(objet);

    float yTitre = y + pourcentagePoliceHauteur/1.2;
    float yTexte = yTitre + pourcentagePoliceHauteur;

    // On dessine la boite, et on la colore
    painter.setPen(pen1);
    QRect rect(x,y,largeurType,hauteur);
    painter.fillRect(rect, *brush);
    painter.drawRoundedRect(rect,3,3);
    QLine lineType(x,y+pourcentagePoliceHauteur,x+largeurType,y+pourcentagePoliceHauteur);
    painter.drawLine(lineType);

    // Si la map(objet, boite) est remplie, on actualise la boite
    if(mapBoiteObjet[objet->getNom()]!=NULL){
        mapBoiteObjet[objet->getNom()]->setX(x);
        mapBoiteObjet[objet->getNom()]->setY(y);
        mapBoiteObjet[objet->getNom()]->setLargeur(largeurType);
        mapBoiteObjet[objet->getNom()]->setHauteur(hauteur);
        mapBoiteObjet[objet->getNom()]->setBrush(brush);
    }


    // Sinon on remplit la map(objet, boite)
    else{
        VisuRDFBoite* boite = new VisuRDFBoite(x, y, largeurType, hauteur);
        boite->setBrush(brush);
        mapBoiteObjet[objet->getNom()]=boite;
    }

    // On inverse la liste des propriétés (pour avoir name en premier)
    list<string> listeNom;
    for(ObjetRDF::iterator it = proprietes.begin(); it!= proprietes.end(); it++){
        string nomProp = (*it).first;
        listeNom.push_front(nomProp);
    }

    // On parcourt la liste des propriétés et on dessine chaque ligne
    for(list<string>::iterator iter = listeNom.begin(); iter!=listeNom.end(); iter++){
        string nom = *iter;
        list<string> valeurs = proprietes[nom];
        list<string>::iterator it2 = valeurs.begin();
        string valeur = *it2;

        if(valeur!=""){

            // On n'affiche que la valeur du type
            if(nom == "type"){
                string valeurType = valeur;
                painter.setPen(pen2);
                f.setBold(true);
                painter.setFont(f);
                painter.drawText(x+1, yTitre, QString(valeurType.c_str()));

            }

            else {
                // On n'affiche que la valeur du name, à côté de la valeur du type
                if(nom == "name"){
                    string valeurName = valeur;
                    painter.setPen(pen2);
                    f.setBold(true);
                    painter.setFont(f);
                    painter.drawText(x+largeurNom, yTitre, QString(valeurName.c_str()));

                }

                else{
                    string nomAffiche = nom + " : ";
                    // On affiche le nom de la propriété
                    painter.setPen(pen1);
                    f.setBold(true);
                    painter.setFont(f);
                    painter.drawText(x+1, yTexte, QString(nomAffiche.c_str()));

                    // On affiche la valeur de la propriété
                    f.setBold(false);
                    painter.setFont(f);
                    // Si la valeur est inférieure à la taille max, on l'affiche sur une ligne
                    if(valeur.size()<=tailleMax){
                        painter.drawText(x+largeurNom, yTexte, QString(valeur.c_str()));
                        yTexte = yTexte + pourcentagePoliceHauteur;
                    }

                    // Sinon on l'affiche sur plusieurs lignes
                    else{
                        // Calcul de nbLignes à revoir (dépend de la taille des mots...)
                        int nbLignes = valeur.size()/tailleMax +1 ;
                        int pos = 0;
                        int posEspace = 0;
                        int precPos = 0;

                        for(int i =0; i< nbLignes; i++){

                            // Si il n'y a aucun espace dans le string
                            if((int)valeur.find(" ",0)==-1){
                                string valeurTronquee = valeur.substr(i*tailleMax,tailleMax);
                                painter.drawText(x+largeurNom, yTexte, QString(valeurTronquee.c_str()));
                                yTexte = yTexte + pourcentagePoliceHauteur;
                            }

                            else{
                                // On met le curseur sur le précédent espace
                                pos = posEspace;
                                int taille = 0;

                                // On cherche le prochain espace pour lequel la suite de mots ne dépasse pas tailleMax
                                while((taille<tailleMax)&(pos!=-1)){
                                    posEspace = pos;
                                    pos = valeur.find(" ", posEspace+1);
                                    taille = pos - precPos;
                                }

                                // On récupère la chaîne à afficher
                                string valeur2;
                                if(i!=nbLignes-1){
                                    valeur2 = valeur.substr(precPos,(posEspace-precPos));
                                }

                                else
                                    valeur2=valeur.substr(precPos);

                                precPos = posEspace;
                                //On affiche la chaine et on fait varier le y
                                painter.drawText(x+largeurNom, yTexte, QString(valeur2.c_str()));
                                yTexte = yTexte + pourcentagePoliceHauteur;
                            }

                        }

                    }
                }
            }
        }

    }


}

/**
 * @brief VisuRDFDessinateur::dessinBoiteParType, dessine les boites du même type les unes sous les autres
 * (la première boite aura les coordonnées x,y)
 * @param type
 * @param x
 * @param y
 * @param painter
 * @param brush
 */
void VisuRDFDessinateur::dessinBoiteParType(VisuRDFType *type, float x, float y, QPainter &painter, QBrush* brush){

    float yBoite = y;

    // On parcourt tous les objets du type

    string nomType = type->getNom();
    set<VisuRDFObjet*> listeObjets = analyseur->getObjetsParType(nomType, true);
    for(set<VisuRDFObjet*>::iterator it = listeObjets.begin(); it!= listeObjets.end(); it++) {

        VisuRDFObjet* objet = *it;
        // On dessine la boite associée à l'objet
        dessinBoite(objet, x, yBoite, painter, brush);
        // On fait varier y pour afficher la prochaine boite en dessous
        yBoite = yBoite + calculHauteurBoite(objet) + espacementVertical;

    }

}

/**
 * @brief VisuRDFDessinateur::dessinModeBoite, dessine les boites de types différents les unes à côté des autres
 * @param painter
 */
void VisuRDFDessinateur::dessinModeBoite(QPainter &painter){

    float x = 20;
    float y = 20;

    int i=0;
    for(set<VisuRDFType*>::iterator it = listeTypes.begin(); it!= listeTypes.end(); it++){
        VisuRDFType* type = *it;
        // Si l'affichage est coloré, on récupère la liste des brush
        cout << "couleur" << couleur << endl;
        if(couleur==1){
            map<int,QBrush*> mapBrush = parametreur->getListePinceau();
            QBrush* brush = mapBrush[i];
            this->dessinBoiteParType(type, x, y, painter,brush);
        }
        else{
            QBrush* brush = new QBrush();
            this->dessinBoiteParType(type, x, y, painter,brush);
        }

        x = x + calculLargeurType(type) + 20;
        i++;
    }


}

/**
 * @brief VisuRDFDessinateur::dessinLiaison, dessine une liaison entre les deux objets
 * @param objet1
 * @param objet2
 * @param painter
 */
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

/**
 * @brief VisuRDFDessinateur::dessinToutesLiaisons, dessine l'ensemble des relations
 * @param painter
 */
void VisuRDFDessinateur::dessinToutesLiaisons(QPainter &painter){

    painter.setPen(pen3);

    //On parcourt la liste des relations et on les dessine
    map<VisuRDFObjet*, list<VisuRDFObjet*> > mapRelations = analyseur->getRelations();
    for(map<VisuRDFObjet*, list<VisuRDFObjet*> >::iterator iter = mapRelations.begin(); iter!= mapRelations.end(); iter++){
        VisuRDFObjet* objet1 = (*iter).first;
        list<VisuRDFObjet*> objets = mapRelations[objet1];
        for(list<VisuRDFObjet*>::iterator it2 = objets.begin(); it2!= objets.end(); it2++){
            VisuRDFObjet* objet2 = *it2;
            dessinLiaison(objet1,objet2, painter);
        }
    }

}

/**
 * @brief VisuRDFDessinateur::dessin, dessine la représentation (en fonction du mode, appelle dessinModeTableau ou dessinModeBoite)
 * @param painter
 */
void VisuRDFDessinateur::dessin(QPainter &painter){
    if (mode=="tableau"){
        dessinModeTableau(painter);
    }

    else{
        dessinModeBoite(painter);
    }

    dessinToutesLiaisons(painter);
    isFirst = false;
}

/**
 * @brief VisuRDFDessinateur::dessinMap, parcourt les map (objet,boite) et (type,boite) pour dessiner la représentation
 * (cette fonction est appellée pour redessiner les objets quand on les bouge dans la fenêtre)
 * @param painter
 */
void VisuRDFDessinateur::dessinMap(QPainter &painter){

    if(isFirst){
        cout << "dessinMap impossible : les maps ne sont pas remplies" << endl;
    }

    else{
        if(mode=="boite"){
            for (boiteObjet::iterator it = mapBoiteObjet.begin(); it!=mapBoiteObjet.end(); it++){
                string nomObjet = (*it).first;
                VisuRDFBoite* boite = mapBoiteObjet[nomObjet];
                VisuRDFObjet* objet = analyseur->getObjetparNom(nomObjet);
                dessinBoite(objet,boite->getX(),boite->getY(),painter,boite->getBrush());
            }
        }

        else{
            for(boiteObjet::iterator iter = mapBoiteType.begin(); iter!=mapBoiteType.end(); iter++){
                string nomType = (*iter).first;
                VisuRDFBoite* boite = mapBoiteType[nomType];
                VisuRDFType* type = analyseur->getTypeParNom(nomType,true);
                dessinTableau(type,boite->getX(),boite->getY(),painter);
            }
        }
        dessinToutesLiaisons(painter);
    }
}

/**
 * @brief VisuRDFDessinateur::recupererBoite
 * @param xOrigine
 * @param yOrigine
 * @return la boite qui se trouve aux coordonnées données, NULL sinon
 */
VisuRDFBoite* VisuRDFDessinateur::recupererBoite(int xOrigine, int yOrigine){

    // Cas du mode boite
    if(mode=="boite"){
        //On parcourt toutes les boites des objets
        for(boiteObjet::iterator it = mapBoiteObjet.begin(); it!=mapBoiteObjet.end(); it++){
            string nomObjet = (*it).first;
            VisuRDFBoite* boite = mapBoiteObjet[nomObjet];
            float xBoite = boite->getX();
            float yBoite = boite->getY();
            float hauteur = boite->getHauteur();
            float largeur = boite->getLargeur();

            // Si la boite occupe les coordonnées xOrigine, yOrigine, on modifie ses coordonnées
            if((xOrigine>=xBoite)&(xOrigine<=xBoite+largeur)&(yOrigine>=yBoite)&(yOrigine<=yBoite+hauteur)){
                // On calcule le dX et dY (pour savoir à quel endroit de la boite on a cliqué)
                dX = xOrigine-xBoite;
                dY = yOrigine-yBoite;
                return boite;
            }
        }
    }

    // Cas du mode tableau
    else{
        //On parcourt tous les tableaux
        for(boiteObjet::iterator iter = mapBoiteType.begin(); iter!=mapBoiteType.end(); iter++){
            string nomType = (*iter).first;
            VisuRDFBoite* boite = mapBoiteType[nomType];
            int xBoite = boite->getX();
            int yBoite = boite->getY();
            int hauteur = boite->getHauteur();
            int largeur = boite->getLargeur();
            // Si le tableau occupe les coordonnées xOrigine, yOrigine, on modifie ses coordonnées
            if((xOrigine>=xBoite)&(xOrigine<=xBoite+largeur)&(yOrigine>=yBoite)&(yOrigine<=yBoite+hauteur)){
                // On calcule le dX et dY (pour savoir à quel endroit de la boite on a cliqué)
                dX = xOrigine-xBoite;
                dY = yOrigine-yBoite;
                return boite;

            }

        }
    }

    return NULL;

}

/**
 * @brief VisuRDFDessinateur::actualiserMapBoite, met à jour les coordonnées de la boite
 * @param boite
 * @param x
 * @param y
 */
void VisuRDFDessinateur::actualiserMapBoite(VisuRDFBoite *boite, int x, int y){

    if(boite!=NULL){
        // Cas du mode boite
        if(mode=="boite"){

            boite->setX(x-dX);
            boite->setY(y-dY);

        }

        // Cas du mode tableau
        else{

            int yBoite = boite->getY();
            boite->setX(x-dX);
            boite->setY(y-dY);
            string nomType;
            for( boiteObjet::iterator iter = mapBoiteType.begin(); iter!=mapBoiteType.end(); iter++)
                if((*iter).second == boite)
                    nomType = (*iter).first;
            cout << "nomType : " << nomType << endl;
            // On modifie les coordonnées des boites des objets du tableau
            set<VisuRDFObjet*> objets = analyseur->getObjetsParType(nomType,true);
            for(set<VisuRDFObjet*>::iterator it = objets.begin(); it!= objets.end(); it++){
                VisuRDFObjet* objet = *it;
                VisuRDFBoite* boiteObj = mapBoiteObjet[objet->getNom()];
                int yObj = boiteObj->getY();
                boiteObj->setX(x-dX);
                boiteObj->setY(yObj-yBoite+y-dY);
            }

        }
    }

}



/**
 * @brief VisuRDFDessinateur::calculLargeurDessin
 * @return largeur totale du dessin
 */
float VisuRDFDessinateur::calculLargeurDessin(){

    float largeur;
    for(boiteObjet::iterator it = mapBoiteObjet.begin(); it!= mapBoiteObjet.end(); it++){
        string nomObjet = (*it).first;
        VisuRDFBoite* boite = mapBoiteObjet[nomObjet];
        float x = boite->getX();
        float largeurBoite = boite->getLargeur();
        if(x+largeurBoite > largeur)
            largeur = x+largeurBoite;

    }
    return largeur + 20;

}

/**
 * @brief Dessinateur::calculHauteurDessin
 * @return hauteur totale du dessin
 */

float VisuRDFDessinateur::calculHauteurDessin() {

    float hauteur;
    for(boiteObjet::iterator it = mapBoiteObjet.begin(); it!= mapBoiteObjet.end(); it++){
        string nomObjet = (*it).first;
        VisuRDFBoite* boite = mapBoiteObjet[nomObjet];
        float y = boite->getY();
        float hauteurBoite = boite->getHauteur();
        if(y+hauteurBoite > hauteur)
            hauteur = y+hauteurBoite;

    }
    return hauteur + 20;
}
