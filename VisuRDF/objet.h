#ifndef OBJET_H
#define OBJET_H
#include <QString>
<<<<<<< HEAD
#include <QMap>
#include "visurdfextractor.h"
=======
#include <map>
#include <list>
#include <iostream>
#include <string>
#include "visurdfextractor.h"

using namespace std;

typedef map<string,string> proprieteMap;
>>>>>>> marjo

class Objet
{
public:
<<<<<<< HEAD

    Objet(int id, std::string nomType, ObjetRDF proprietes);
=======
    int id;
    string nomType;
    ObjetRDF proprietes;
    int largeurMax;

    Objet(int id, string nomType, ObjetRDF proprietes);
>>>>>>> marjo
    ~Objet();

    void setLargeur();
    string getNomType();
    ObjetRDF getProprietes();
    int getLargeur();

private :

    int id;
    std::string nomType;
    ObjetRDF proprietes;
    int largeurMax;


};

#endif // OBJET_H
