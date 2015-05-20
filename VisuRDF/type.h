#ifndef TYPE_H
#define TYPE_H
#include <QString>
#include <list>

class Type
{
public:

    QString nomType;

    int nbObjets;
    list<QString> proprietesNonVides;

    Type(QString nomType);
    ~Type();
    void setProprietes(list<QString>);
    void setNbObjet(int);
    int getNbObjet();
    list<QString> getProprietes();
    QString getNom();

};

#endif // TYPE_H
