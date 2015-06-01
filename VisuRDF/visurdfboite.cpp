#include "visurdfboite.h"

VisuRDFBoite::VisuRDFBoite(float x, float y, float largeur, float hauteur) : x(x), y(y), largeur(largeur), hauteur(hauteur)
{

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

float VisuRDFBoite::getLargeur(){
    return largeur;
}

float VisuRDFBoite::getHauteur(){
    return hauteur;
}

