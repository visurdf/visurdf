#ifndef VISURDFTYPE_H
#define VISURDFTYPE_H
#include <QString>
#include <list>

using namespace std;

class VisuRDFType
{
public:

    VisuRDFType(std::string nomType);
    ~VisuRDFType();
    void setProprietes(std::list<std::string>);
    void setNbObjet(int);
    int getNbObjet();
    std::list<std::string> getProprietes();
    std::string getNom();
    string toString(){

        string tostring = "{Type: ";
        string strprop = ", Props: [";
        typedef list<string> ::const_iterator ListIterator;
        int i =0;
        for(ListIterator itr = proprietesNonVides.begin(); itr != proprietesNonVides.end(); itr++ ){
            strprop.append(*itr);
            if(i  != (int)(proprietesNonVides.size() -1))
                strprop.append(", ");
            i++;
        }
        strprop.append("]");


        return tostring
                .append(nomType)
                .append(strprop)
                .append("}");}

    int getNombreRelations();
    void setNombreRelations(int _nombre);

private :

    std::string nomType;
    int nbObjets;
    std::list<std::string> proprietesNonVides;
    int nombreRelations;

};

#endif // VISURDFTYPE_H
