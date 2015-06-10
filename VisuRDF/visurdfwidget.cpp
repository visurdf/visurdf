#include "visurdfwidget.h"
#include "ui_visurdfwidget.h"

visuRDFWidget::visuRDFWidget(VisuRDFDessinateur *_dessinateur)
{
    dessinateur = _dessinateur;

}

visuRDFWidget::~visuRDFWidget()
{

}

void visuRDFWidget::paintEvent(QPaintEvent *qpe){
    QWidget::paintEvent(qpe);
    QPainter painter(this);

    dessinateur->dessin(painter);


}
