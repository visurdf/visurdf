#ifndef OBJET_H
#define OBJET_H
#include <QString>
#include <QMap>
#include "visurdfextractor.h"

class Objet
{
public:

    Objet(int id, std::string nomType, ObjetRDF proprietes);
    ~Objet();
    void setLargeur(int l);

private :

    int id;
    std::string nomType;
    ObjetRDF proprietes;
    int largeurMax;


};

#endif // OBJET_H
