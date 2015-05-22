#ifndef OBJET_H
#define OBJET_H
#include <QString>
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
    int id;
    Type * type;
    ObjetRDF proprietes;
    int largeurMax;

    Objet(int id, Type *type , ObjetRDF proprietes);
    ~Objet();

    void setLargeur();
    Type* getType();
    ObjetRDF getProprietes();
    int getLargeur();


};

#endif // OBJET_H
