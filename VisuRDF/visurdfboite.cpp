#include "visurdfboite.h"

VisuRDFBoite::VisuRDFBoite(float x, float y, float largeur, float hauteur) : x(x), y(y), largeur(largeur), hauteur(hauteur)
{
    brush = QBrush();
}


VisuRDFBoite::~VisuRDFBoite()
{

}

/**
 * @brief VisuRDFBoite::getX
 * @return coordonnée x de la boite
 */
float VisuRDFBoite::getX(){
    return x;
}

/**
 * @brief VisuRDFBoite::getY
 * @return coordonnée y de la boite
 */
float VisuRDFBoite::getY(){
    return y;
}

/**
 * @brief VisuRDFBoite::setX
 * @param new_x
 */
void VisuRDFBoite::setX(float new_x){
    x = new_x;
}

/**
 * @brief VisuRDFBoite::setY
 * @param new_y
 */
void VisuRDFBoite::setY(float new_y){
    y = new_y;
}

/**
 * @brief VisuRDFBoite::setLargeur
 * @param new_largeur
 */
void VisuRDFBoite::setLargeur(float new_largeur){
    largeur = new_largeur;
}

/**
 * @brief VisuRDFBoite::getLargeur
 * @return largeur de la boite
 */
float VisuRDFBoite::getLargeur(){
    return largeur;
}

/**
 * @brief VisuRDFBoite::getHauteur
 * @return hauteur de la boite
 */
float VisuRDFBoite::getHauteur(){
    return hauteur;
}

/**
 * @brief VisuRDFBoite::setHauteur
 * @param new_hauteur
 */
void VisuRDFBoite::setHauteur(float new_hauteur){
    hauteur = new_hauteur;
}

/**
 * @brief VisuRDFBoite::getBrush
 * @return couleur de la boite (QBrush)
 */
QBrush VisuRDFBoite::getBrush(){
    return brush;
}

/**
 * @brief VisuRDFBoite::setBrush
 * @param newBrush
 */
void VisuRDFBoite::setBrush(QBrush newBrush){
    brush = newBrush;
}
