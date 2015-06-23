
#include "visurdfextracteur.h"
#include <QApplication>
#include "visurdfanalyseur.h"
#include "visurdfdessinateur.h"
#include "visurdfparametreur.h"
#include "visurdfwidget.h"
#include "mainwindow.h"
#include <QTextCodec>


int main(int argc, char *argv[])
{
    // Encodage UTF-8
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication A(argc,argv);

     MainWindow* window = new MainWindow();
     window->show();

    return A.exec();
}



