#ifndef OBJET_H
#define OBJET_H
#include <QString>
#include <QMap>

class Objet
{
public:
    int id;
    QString nomType;
    QMap<QString, QString> proprietes;
    int largeurMax;

    Objet(int id, QString nomType, QMap<QString,QString> proprietes);
    ~Objet();
    void setLargeur(int l);




};

#endif // OBJET_H
