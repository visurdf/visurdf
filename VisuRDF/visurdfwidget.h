#ifndef VISURDFWIDGET_H
#define VISURDFWIDGET_H
#include "visurdfdessinateur.h"
#include <QWidget>
#include <QMouseEvent>
#include <string.h>
#include <QSvgGenerator>

#include <QWidget>

class visuRDFWidget : public QWidget
{
    Q_OBJECT

public:
    explicit visuRDFWidget();
    ~visuRDFWidget();
    virtual void paintEvent(QPaintEvent * qpe);
    virtual void mousePressEvent(QMouseEvent * qme);
    virtual void mouseMoveEvent(QMouseEvent * qme);
    virtual void mouseReleaseEvent(QMouseEvent * qme);
    virtual void open();
    virtual void print();
    virtual void printPNG();
    virtual void changePourcentagePolice(int p);
    virtual void changePourcentagePoliceH(int p);
    virtual void changeColoration(int c);
    virtual void changeMode(string mode);
    virtual void changePolice(QFont f);
    virtual void changeTaillePolice(int p);

private:
    VisuRDFDessinateur * dessinateur;
    VisuRDFAnalyseur* analyseur;
    bool rdfChoisi;
    bool dessinModifie;
    bool firstDessin;

    VisuRDFBoite* boiteChoisie;

    QPoint posSouris;


};

#endif // VISURDFWIDGET_H
