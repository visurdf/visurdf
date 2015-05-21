#ifndef TYPE_H
#define TYPE_H
#include <QString>
#include <list>

using namespace std;

class Type
{
public:

    Type(std::string nomType);
    ~Type();
    void setProprietes(std::list<std::string>);
    void setNbObjet(int);
    int getNbObjet();
    std::list<std::string> getProprietes();
    std::string getNom();

private :

    std::string nomType;
    int nbObjets;
    std::list<std::string> proprietesNonVides;

};

#endif // TYPE_H
