#ifndef VISURDFWIDGET_H
#define VISURDFWIDGET_H
#include "visurdfdessinateur.h"
#include "visurdfgenerateur.h"
#include <QWidget>
#include <QMouseEvent>

#include <QWidget>

class visuRDFWidget : public QWidget
{
    Q_OBJECT

public:
    explicit visuRDFWidget();
    ~visuRDFWidget();
    virtual void paintEvent(QPaintEvent * qpe);
    virtual void open();
    virtual void print();

private:
    VisuRDFDessinateur * dessinateur;
    VisuRDFAnalyseur* analyseur;
    VisuRDFGenerateur* generateur;
    bool rdfChoisi;


};

#endif // VISURDFWIDGET_H
