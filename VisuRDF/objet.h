#ifndef OBJET_H
#define OBJET_H
#include <QString>

#include <QMap>
#include "visurdfextractor.h"

#include <map>
#include <list>
#include <iostream>
#include <string>
#include "visurdfextractor.h"
#include "type.h"
using namespace std;


class Objet
{
public:


    Objet(int id, Type type, ObjetRDF proprietes);

    ~Objet();

    void setLargeur();
    Type getNomType();
    ObjetRDF getProprietes();
    int getLargeur();

private :

    int id;
    Type type;
    ObjetRDF proprietes;
    int largeurMax;


};

#endif // OBJET_H
