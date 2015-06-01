#ifndef VISURDFBOITE_H
#define VISURDFBOITE_H


class VisuRDFBoite
{
public:
    VisuRDFBoite(float x, float y, float largeur, float hauteur);
    ~VisuRDFBoite();
    float getX();
    float getY();
    float getLargeur();
    float getHauteur();


private:
    float x;
    float y;
    float largeur;
    float hauteur;

};

#endif // VISURDFBOITE_H
