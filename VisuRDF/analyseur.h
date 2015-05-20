#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <iostream>
#include <list>
#include <objet.h>
#include <type.h>

class analyseur
{
public:
    analyseur();
    ~analyseur();
    std::list<Objet> getTousLesObjets();
    std::list<Type> getTousLesTypes();

private:
    std::list<Objet> tousLesObjets;
    std::list<Type> tousLesTypes;
};

#endif // ANALYSEUR_H
