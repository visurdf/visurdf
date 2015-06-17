#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visurdfextracteur.h"
#include "visurdfclassesvg.h"
#include "visurdfanalyseur.h"
#include "visurdfdessinateur.h"
#include "visurdfgenerateur.h"
#include "visurdfparametreur.h"
#include <vector>
#include <QTextCodec>
#include <QScrollArea>
#include <QPushButton>
#include "visurdfwidget.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //----- BARRE DE MENU ------//
    //Définition du menu
    QMenuBar * menuBar = this->menuBar();
    QMenu * fileMenu = menuBar->addMenu("&File");


    //Action dans le menu (bouton)
    //----- ACTIONS ------//
    QAction* openAction = new QAction (QIcon(":open.png"),"&Open",this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setToolTip(tr("Open File"));

    QAction* saveAction = new QAction (QIcon(":save.png"),"&Save",this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setToolTip(tr("Save File"));

    QAction* quitAction = new QAction (QIcon(":quit.png"),"&Quit",this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setToolTip(tr("Quit"));

    //----- Boutons choix mode-------//
    QMenu *menuMode = new QMenu();
    QAction *boiteAction = new QAction(tr("&mode boite"),this);
    QAction *tableAction = new QAction(tr("&mode tableau"),this);
    QActionGroup *modeGroupe = new QActionGroup(this);
    modeGroupe->addAction(boiteAction);
    modeGroupe->addAction(tableAction);
    menuMode->addAction(boiteAction);
    menuMode->addAction(tableAction);
    changementMode = new QAction("mode",this);
    changementMode->setMenu(menuMode);

    //---- Bouton choix police -----//
    QMenu* menuPolice = new QMenu();
    QFontDatabase fontDataBase;
    QActionGroup *policeGroupe = new QActionGroup(this);
    list<QString> fontFamilies = fontDataBase.families().toStdList();
    cout<<fontFamilies.size()<<endl;

    for (list<QString>::iterator fontIter = fontFamilies.begin();fontIter != fontFamilies.end();fontIter++){

        QString police = *fontIter;
        QAction * action = new QAction(police,this);

        policeGroupe->addAction(action);
        menuPolice->addAction(action);

    }
    changementPolice = new QAction("police",this);
    changementPolice->setMenu(menuPolice);

    // Encodage UTF-8
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //Déclaration du widget

    RDFWidget = new visuRDFWidget();
    RDFWidget->setMinimumSize(10000,10000);

    QScrollArea* mQScrollArea = new QScrollArea ();
    mQScrollArea ->setWidget(RDFWidget);
//mQScrollArea->setMinimumSize(700,700);
    setCentralWidget(mQScrollArea);

    //Mise en place de la barre de menu
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(quitAction);
    QToolBar * toolBar = this->addToolBar(tr("&File"));

    //Action dans la toolbar

    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(quitAction);
    toolBar->addAction(changementMode);
    toolBar->addAction(changementPolice);

    //Connection des slots
    QObject::connect(openAction, SIGNAL(triggered()),this,SLOT(openFile()));
    QObject::connect(quitAction, SIGNAL(triggered()),this,SLOT(quitApp()));
    QObject::connect(saveAction, SIGNAL(triggered()),this,SLOT(printFile()));
    QObject::connect(modeGroupe, SIGNAL(triggered(QAction*)),this,SLOT(changerMode(QAction*)));
    QObject::connect(policeGroupe, SIGNAL(triggered(QAction*)),this,SLOT(changerPolice(QAction*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quitApp(){
    close();
}

void MainWindow::openFile(){

    RDFWidget->open();

}

void MainWindow::printFile(){
    cout<<"impression"<<endl;
    RDFWidget->print();
}

void MainWindow::changerColoration(){

}

void MainWindow::changerMode(QAction *action){

    if (action->iconText()== "mode tableau"){
        RDFWidget->changeMode("tableau");
        changementMode->setIconText("mode tableau");

    }
    if (action->iconText()== "mode boite"){
        RDFWidget->changeMode("boite");
        changementMode->setIconText("mode boite");
    }
}

void MainWindow::changerPolice(QAction *action){
    RDFWidget->changePolice(action->iconText());
    changementPolice->setIconText(action->iconText());

}


void MainWindow::parametrerPourcentagePolice(){


}

void MainWindow::parametrerPourcentageHPolice(){

}
