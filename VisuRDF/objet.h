#ifndef OBJET_H
#define OBJET_H
#include <QString>
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
    int id;
    string nomType;
    ObjetRDF proprietes;
    int largeurMax;

    Objet(int id, string nomType, ObjetRDF proprietes);
    ~Objet();

    void setLargeur();
    string getNomType();
    ObjetRDF getProprietes();
    int getLargeur();


};

#endif // OBJET_H
