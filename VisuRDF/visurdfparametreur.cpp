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
    pourcentagePolice = 0.7;
    pourcentagePoliceHauteur = 1.2;
    tailleMax = 50;

    couleur = Qt::black;

    //Police par défaut
    QFontDatabase fontDataBase;
    QString firstFont = fontDataBase.families().first();
    police.setFamily(firstFont);
    mode = "tableau";
    fontSize = 6;

    //Couleur par défaut
    QColor color; // = Qt::black;
    color.setRgb(14,50,200);

    penPolice.setColor(Qt::red);
    penContour.setColor(color);
    penLiaison.setColor(Qt::black);

    //Couleur de fond par défaut
    mapPinceau = new map<int,QBrush*>();

    listeCouleur = new list<QColor*>();
    listeCouleur->push_back(new QColor(128,191,255));
    listeCouleur->push_back(new QColor(211,168,255));
    listeCouleur->push_back(new QColor(191,255,128));
    listeCouleur->push_back(new QColor(255,255,128));
    listeCouleur->push_back(new QColor(255,145,145));
    listeCouleur->push_back(new QColor(179,217,255));
    listeCouleur->push_back(new QColor(255,166,210));
    listeCouleur->push_back(new QColor(128,255,128));
    listeCouleur->push_back(new QColor(255,179,102));
    listeCouleur->push_back(new QColor(186,186,186));

    int i = 0;
    for (list<QColor*>::iterator it = listeCouleur->begin(); it != listeCouleur->end();it++){

        QColor* couleur = *it;
        QBrush pinceau = *couleur;
        mapPinceau->insert(std::make_pair(i, new QBrush(pinceau)));
        //mapPinceau[i]=new QBrush(pinceau);
        i++;
        //listPinceau->push_back(new QBrush(pinceau));
    }

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
QPen VisuRDFParametreur::getPenPolice(){
    return penPolice;
}

QPen VisuRDFParametreur::getPenLiaison(){
    return penLiaison;
}

QPen VisuRDFParametreur::getPenContour(){
    return penContour;
}


/**
 * @brief VisuRDFParametrage::getParamPolice
 * retourne
 * @return QFont police
 */
QFont VisuRDFParametreur::getParamPolice(){
    return police;
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

map<int,QBrush*> VisuRDFParametreur::getListePinceau(){
    return *mapPinceau;
}

float VisuRDFParametreur::getPourcentagePolice(){
    return pourcentagePolice;
}

float VisuRDFParametreur::getPourcentagePoliceHauteur(){
    return pourcentagePoliceHauteur;
}

float VisuRDFParametreur::getTailleMax(){
    return tailleMax;
}

void VisuRDFParametreur::setPourcentagePolice(int p){
    if (p > 0)
        pourcentagePolice = p;
    else
        cerr<<"le paramètre pourcentage police doit être positif"<<endl;
}


void VisuRDFParametreur::setPourcentageHPolice(int p){
    if (p > 0)
        pourcentagePoliceHauteur = p;
    else
        cerr<<"le paramètre pourcentage police hauteur doit être positif"<<endl;
}

void VisuRDFParametreur::setColoration(int c){
    coloration = c;
}

void VisuRDFParametreur::setMode(string _mode){
    if (_mode!="tableau" && _mode!="boite")
        cerr<<"le mode parametrer n'est pas correcte"<<endl;
    else
        mode = _mode;
}

void VisuRDFParametreur::setPolice(QString _police){
    police.setFamily(_police);
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
                coloration = atoi(enfant.attribute("value",0).toStdString().c_str());
                cout << "l'affichage sera coloré : "<< coloration << endl;

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
        else if (enfant.tagName()=="pourcentagePoliceHauteur"){
            if (enfant.attribute("value",0)!= 0){
                QString attribut = enfant.attribute("value",0);
                pourcentagePoliceHauteur = attribut.toFloat();
               // pourcentagePoliceHauteur = atof(enfant.attribute("value",0).toStdString().c_str());
                cout << "le pourcentage hauteur police sera : "<< pourcentagePoliceHauteur<< endl;
            }
        }
        else if (enfant.tagName()=="pourcentagePolice"){
            if (enfant.attribute("value",0)!= 0){
                QString attribut = enfant.attribute("value",0);
                pourcentagePolice = attribut.toFloat();
               // pourcentagePolice = atof(enfant.attribute("value",0).toStdString().c_str());
                cout << "le pourcentage police sera : "<< pourcentagePolice<< endl;
            }
        }
        else if (enfant.tagName()=="tailleMax"){
            if (enfant.attribute("value",0)!= 0){
                QString attribut = enfant.attribute("value",0);
                tailleMax = attribut.toFloat();
                //tailleMax = atof(enfant.attribute("value",0).toStdString().c_str());
                cout << "la taille max des propriétés sera : "<< tailleMax<< endl;
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

