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

using namespace std;

typedef map<string,string> proprieteMap;


class Objet
{
public:


    Objet(int id, string nomType, ObjetRDF proprietes);

    ~Objet();

    void setLargeur();
    string getNomType();
    ObjetRDF getProprietes();
    int getLargeur();

private :

    int id;
    string nomType;
    ObjetRDF proprietes;
    int largeurMax;


};

#endif // OBJET_H
