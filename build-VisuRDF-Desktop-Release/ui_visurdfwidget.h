/********************************************************************************
** Form generated from reading UI file 'visurdfwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISURDFWIDGET_H
#define UI_VISURDFWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_visuRDFWidget
{
public:

    void setupUi(QWidget *visuRDFWidget)
    {
        if (visuRDFWidget->objectName().isEmpty())
            visuRDFWidget->setObjectName(QString::fromUtf8("visuRDFWidget"));
        visuRDFWidget->resize(400, 300);

        retranslateUi(visuRDFWidget);

        QMetaObject::connectSlotsByName(visuRDFWidget);
    } // setupUi

    void retranslateUi(QWidget *visuRDFWidget)
    {
        visuRDFWidget->setWindowTitle(QApplication::translate("visuRDFWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class visuRDFWidget: public Ui_visuRDFWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISURDFWIDGET_H
