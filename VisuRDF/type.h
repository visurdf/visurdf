#ifndef TYPE_H
#define TYPE_H
#include <QString>
#include <list>

class Type
{
public:

    Type(QString nomType);
    ~Type();
    void setProprietes(std::list<QString>);
    void setNbObjet(int);
    int getNbObjet();
    std::list<QString> getProprietes();
    QString getNom();

private :

    QString nomType;
    int nbObjets;
    std::list<QString> proprietesNonVides;

};

#endif // TYPE_H
