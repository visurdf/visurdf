#ifndef VISURDFBOITE_H
#define VISURDFBOITE_H
#include <QBrush>

class VisuRDFBoite
{
public:
    VisuRDFBoite(float x, float y, float largeur, float hauteur);
    ~VisuRDFBoite();
    float getX();
    float getY();
    float getLargeur();
    float getHauteur();
    void setX(float);
    void setY(float);
    void setHauteur(float);
    void setLargeur(float);
    QBrush* getBrush();
    void setBrush(QBrush*);


private:
    float x;
    float y;
    float largeur;
    float hauteur;
    QBrush* brush;
};

#endif // VISURDFBOITE_H
