#include "visurdfparametreur.h"



#include <string>


#include <QtXml>
#include <QMessageBox>

using namespace std;
/**
 * @brief VisuRDFParametrage::VisuRDFParametrage
 * Constructeur du lecteur de paramètres
 * sans paramètres, la couleur est noire, avec un mode tableau
 *
 */
VisuRDFParametreur::VisuRDFParametreur() : QWidget(){
    //Parametre par défaut du dessin si les informations ne sont pas contenu dans le fichier xml
    interligne = 1;

    couleur = Qt::black;

    QFontDatabase fontDataBase;
    QString firstFont = fontDataBase.families().first();
    police.setFamily(firstFont);
    mode = "tableau";
    fontSize = 6;

}

VisuRDFParametreur::~VisuRDFParametreur(){

}

/**
 * @brief VisuRDFParametrage::getParamCouleur
 * retourne la couleur lu par le fichier de paramètre
 * @return QColor couleur
 *
 */
QColor VisuRDFParametreur::getParamCouleur(){
    return couleur;
}

/**
 * @brief VisuRDFParametrage::getParamPen
 * retourne la valeur des pen du fichier de parametrage
 * @return QPen pen
 */
QPen VisuRDFParametreur::getParamPen(){
    return pen;
}

/**
 * @brief VisuRDFParametrage::getParamPolice
 * retourne
 * @return QFont police
 */
QFont VisuRDFParametreur::getParamPolice(){
    return police;
}


int VisuRDFParametreur::getParamInterligne(){
    return interligne;
}

int VisuRDFParametreur::getParamColoration(){
    return coloration;
}

int VisuRDFParametreur::getFontSize(){
    return fontSize;
}

string VisuRDFParametreur::getParamMode(){
    return mode;
}


/**
 * @brief VisuRDFParametrage::lectureParametres
 * fonction parcourant le fichier de paramètre parametres.xml situé dans le dossier du programme
 */
void VisuRDFParametreur::lectureParametres(){

    QDomDocument *dom = new QDomDocument("fichier de parmatres");
    QFile parametres("parametres.xml");// On choisit le fichier contenant les informations XML.

    if(!parametres.open(QIODevice::ReadOnly)){// Si l'on n'arrive pas à ouvrir le fichier XML.{
        QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n' pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
        return;
    }

    if (!dom->setContent(&parametres)){ // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.

        parametres.close();
        QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
        return;
    }

    QDomElement dom_element = dom->documentElement();
    QDomElement enfant = dom_element.firstChild().toElement();

    //Pour l'affichage dans la console
    cout<<endl<<"*******************************************"<<endl;
    cout<< "lecture du fichier de parametrage"<<endl<<endl;

    // Lecture du fichier XML et remplissage de attribut de l'objet parametreur
    while (!enfant.isNull()) {

        if (enfant.tagName()=="couleur"){
            if (enfant.attribute("value",0) != 0){
                QString Couleur = enfant.attribute("value",0);
                couleur = Couleur;
                cout << "La couleur est "<< couleur.value()<< endl;
            }
        }
        else if (enfant.tagName()=="mode"){
            if (enfant.attribute("value",0)!= 0){
                mode = enfant.attribute("value",0).toStdString();
                cout << "le mode d'affichage est : "<< mode<<endl;

            }
        }
        else if (enfant.tagName()=="coloration"){
            if (enfant.attribute("value",0)!= 0){
                coloration = 1;
                cout << "l'affichage sera coloré"<<endl;

            }
        }
        else if (enfant.tagName()=="interligne"){
            if (enfant.attribute("value",0)!= 0){
                interligne = atoi(enfant.attribute("value",0).toStdString().c_str());
                cout << "la valeur de l'interligne sera : "<< interligne<< endl;

            }

        }
        else if (enfant.tagName()=="taillePolice"){
            if (enfant.attribute("value",0)> 0){
                fontSize = atoi(enfant.attribute("value",0).toStdString().c_str());
                cout << "la taille de la police sera : "<< fontSize<< endl;

            }


        }
        else if (enfant.tagName()=="police"){
            if (enfant.attribute("value",0)!= 0){
                police.setFamily( enfant.attribute("value",0));
                cout << "le type de police sera : "<< police.family().toStdString()<< endl;

            }


        }
        else cout << "le tag : '"<<enfant.tagName().toStdString()
                  <<"' n'est pas reconnu dans le fichier de parametrage"
                  << endl;


        enfant = enfant.nextSibling().toElement();
    }


    parametres.close(); // Dans tous les cas, on doit fermer le document XML : on n'en a plus besoin, tout est compris dans l'objet DOM.

    cout<<endl<<"Fin de la lecture du fichier de paramètres"<<endl;
    cout<<"*******************************************"<<endl;
}

