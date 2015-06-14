#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visurdfextracteur.h"
#include "visurdfclassesvg.h"
#include "visurdfanalyseur.h"
#include "visurdfdessinateur.h"
#include "visurdfgenerateur.h"
#include "visurdfparametreur.h"
#include <QTextCodec>
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
    cout<< "ici"<<endl;

    QAction* saveAction = new QAction (QIcon(":save.png"),"&Save",this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setToolTip(tr("Save File"));


    QAction* quitAction = new QAction (QIcon(":quit.png"),"&Quit",this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setToolTip(tr("Quit"));


    // Encodage UTF-8
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //Déclaration du widget

    RDFWidget = new visuRDFWidget();
    setCentralWidget(RDFWidget);

    //Mise en place de la barre de menu
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(quitAction);
    QToolBar * toolBar = this->addToolBar(tr("&File"));

    //Action dans la toolbar

    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(quitAction);

    //Connection des slots
    QObject::connect(openAction, SIGNAL(triggered()),this,SLOT(openFile()));
    QObject::connect(quitAction, SIGNAL(triggered()),this,SLOT(quitApp()));
    QObject::connect(saveAction, SIGNAL(triggered()),this,SLOT(printFile()));



    cout<< "ici"<<endl;

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
