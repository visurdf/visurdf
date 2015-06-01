#ifndef VISURDFOBJET_H
#define VISURDFOBJET_H
#include <QString>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include "visurdfextracteur.h"
#include "visurdftype.h"

using namespace std;


class VisuRDFObjet
{
public:
    /*int id;
    Type * type;
    ObjetRDF proprietes;
    int largeurMax;*/

   // Objet(int id, Type type, ObjetRDF proprietes);
    VisuRDFObjet(VisuRDFType *type , ObjetRDF proprietes);
    ~VisuRDFObjet();

    void setLargeur();
    VisuRDFType* getType();
    ObjetRDF getProprietes();
   // int getLargeur();
    string getNom();
    string toString();


private :


    VisuRDFType *type;
    ObjetRDF proprietes;
  //  int largeurMax;

};


#endif // VISURDFOBJET_H
