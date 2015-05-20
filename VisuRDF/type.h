#ifndef TYPE_H
#define TYPE_H
#include <QString>
#include <list>

class Type
{
public:

    QString nomType;

    int nbObjets;
    std::list<QString> proprietesNonVides;

    Type(QString nomType);
    ~Type();
    void setProprietes(std::list<QString>);
    void setNbObjet(int);
    int getNbObjet();
    std::list<QString> getProprietes();
    QString getNom();

};

#endif // TYPE_H
