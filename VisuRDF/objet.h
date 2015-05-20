#ifndef OBJET_H
#define OBJET_H
#include <QString>
#include <QMap>

class Objet
{
public:

    Objet(int id, QString nomType, QMap<QString,QString> proprietes);
    ~Objet();
    void setLargeur(int l);

private :

    int id;
    QString nomType;
    QMap<QString, QString> proprietes;
    int largeurMax;


};

#endif // OBJET_H
