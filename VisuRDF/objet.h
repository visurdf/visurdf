#ifndef OBJET_H
#define OBJET_H
#include <QString>
#include <map>
#include <list>
#include <iostream>
#include <string>
using namespace std;

typedef map<string,string> proprieteMap;

class Objet
{
public:
    int id;
    string nomType;
    proprieteMap proprietes;
    int largeurMax;

    Objet(int id, string nomType, proprieteMap proprietes);
    ~Objet();

    void setLargeur();
    string getNomType();
    proprieteMap getProprietes();
    int getLargeur();


};

#endif // OBJET_H
