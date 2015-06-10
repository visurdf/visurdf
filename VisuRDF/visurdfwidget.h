#ifndef VISURDFWIDGET_H
#define VISURDFWIDGET_H
#include "visurdfdessinateur.h"
#include <QWidget>
#include <QMouseEvent>

#include <QWidget>

class visuRDFWidget : public QWidget
{
    Q_OBJECT

public:
    explicit visuRDFWidget(VisuRDFDessinateur *dessinateur);
    ~visuRDFWidget();
    virtual void paintEvent(QPaintEvent * qpe);

private:
    VisuRDFDessinateur * dessinateur;



};

#endif // VISURDFWIDGET_H
