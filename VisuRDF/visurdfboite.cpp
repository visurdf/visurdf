#include "visurdfboite.h"

VisuRDFBoite::VisuRDFBoite(float x, float y, float largeur, float hauteur) : x(x), y(y), largeur(largeur), hauteur(hauteur)
{

    brush = new QBrush();
}

VisuRDFBoite::~VisuRDFBoite()
{

}

float VisuRDFBoite::getX(){
    return x;
}

float VisuRDFBoite::getY(){
    return y;
}

void VisuRDFBoite::setX(float new_x){
    x = new_x;
}

void VisuRDFBoite::setY(float new_y){
    y = new_y;
}

float VisuRDFBoite::getLargeur(){
    return largeur;
}

float VisuRDFBoite::getHauteur(){
    return hauteur;
}

QBrush* VisuRDFBoite::getBrush(){
    return brush;
}

void VisuRDFBoite::setBrush(QBrush * newBrush){
    brush = newBrush;
}
