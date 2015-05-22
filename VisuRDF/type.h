#ifndef TYPE_H
#define TYPE_H
#include <QString>
#include <set>


using namespace std;

class Type
{
public:

    Type(std::string nomType);
    ~Type();
    void setProprietes(std::set<std::string>);
    void setNbObjet(int);
    int getNbObjet();
    std::set<std::string> getProprietes();
    std::string getNom();
    string toString(){

        string tostring = "{Type: ";
        string strprop = ", Props: [";
        typedef set<string> ::const_iterator ListIterator;
        int i =0;
        for(ListIterator itr = proprietesNonVides.begin(); itr != proprietesNonVides.end(); itr++ ){
            strprop.append(*itr);
            if(i  != proprietesNonVides.size() -1)
                strprop.append(", ");
            i++;
        }
        strprop.append("]");


        return tostring
                .append(nomType)
                .append(strprop)
                .append("}");}

private :

    string nomType;
    int nbObjets;
    set<std::string> proprietesNonVides;

};

#endif // TYPE_H
