#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visurdfextracteur.h"
#include "visurdfanalyseur.h"
#include "visurdfdessinateur.h"
#include "visurdfgenerateur.h"
#include "visurdfparametreur.h"
#include <vector>
#include <QTextCodec>
#include <QScrollArea>
#include <QPushButton>
#include <QComboBox>
#include <QFontComboBox>
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

    //-------Choix parametre police-------//
    QComboBox * boxLargeur = new QComboBox();
    QComboBox * boxHauteur = new QComboBox();
    QComboBox * boxTaillePolice = new QComboBox();
    QFontComboBox * boxFont = new QFontComboBox();

    float i = 0;
    while (i < 2){
        ostringstream oss;

        i += 0.1;
        oss << i;

        QString value = oss.str().c_str();
        QString textBox("coef largeur : " + value);
        boxLargeur->addItem(textBox);
    }
    i = 0;
    while (i < 2){
        ostringstream oss;

        i += 0.1;
        oss << i;

        QString value = oss.str().c_str();
        QString textBox("coef hauteur : " + value);
        boxHauteur->addItem(textBox);
    }
    i =0;
    while (i < 20){
        ostringstream oss;

        i += 1;
        oss << i;

        QString value = oss.str().c_str();
        QString textBox("taille police: " + value);
        boxTaillePolice->addItem(textBox);
    }

    VisuRDFParametreur parametreur;
    parametreur.lectureParametres();

    //----- Boutons choix couleur-------//
    int coloration = parametreur.getParamColoration();
    cout << "mise en place : "<<coloration <<endl;
    //string textMode = parametreur.getParamMode();
    QString textBoutonColoration;


    if ( coloration == 0)
        textBoutonColoration = "Sans Couleur";
    else
        textBoutonColoration = "Avec Couleur";
    colorationButton = new QPushButton(textBoutonColoration,this);

    ostringstream ss;
    ss << parametreur.getParamMode();
    QString textMode = ss.str().c_str();
    QString textBoutonMode = "mode " + textMode ;

    changementMode = new QAction(textBoutonMode ,this);
    changementMode->setMenu(menuMode);


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
    QToolBar * toolBarMenu = this->addToolBar(tr("&File"));
    QToolBar * toolBarParam = this->addToolBar(tr("&Parametre"));

    //Action dans la toolbar

    toolBarMenu->addAction(openAction);
    toolBarMenu->addAction(saveAction);
    toolBarMenu->addAction(quitAction);
    toolBarParam->addAction(changementMode);
    toolBarParam->addWidget(boxLargeur);
    toolBarParam->addWidget(boxHauteur);
    toolBarParam->addWidget(boxFont);
    toolBarParam->addWidget(boxTaillePolice);
    toolBarParam->addWidget(colorationButton);
    boxLargeur->setCurrentIndex(parametreur.getPourcentagePolice()*10 - 1);
    boxHauteur->setCurrentIndex(parametreur.getPourcentagePoliceHauteur()*10 - 1);
    boxTaillePolice->setCurrentIndex(parametreur.getFontSize()- 1);

    //Connection des slots
    QObject::connect(openAction, SIGNAL(triggered()),this,SLOT(openFile()));
    QObject::connect(quitAction, SIGNAL(triggered()),this,SLOT(quitApp()));
    QObject::connect(saveAction, SIGNAL(triggered()),this,SLOT(printFile()));
    QObject::connect(modeGroupe, SIGNAL(triggered(QAction*)),this,SLOT(changerMode(QAction*)));
    QObject::connect(boxLargeur,SIGNAL(currentIndexChanged(int)),this,SLOT(parametrerPourcentagePolice(int)));
    QObject::connect(boxHauteur,SIGNAL(currentIndexChanged(int)),this,SLOT(parametrerPourcentageHPolice(int)));
    QObject::connect(boxFont,SIGNAL(currentFontChanged(QFont)),this,SLOT(changerPolice(QFont )));
    QObject::connect(boxTaillePolice,SIGNAL(currentIndexChanged(int)),this,SLOT(parametrerTaillePolice(int)));
    QObject::connect(colorationButton,SIGNAL(clicked()),this,SLOT(changerColoration()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::quitApp : ferme l'application
 */
void MainWindow::quitApp(){
    close();
}

/**
 * @brief MainWindow::openFile : appelle la fonction d'ouverture fichier
 */
void MainWindow::openFile(){

    RDFWidget->open();

}

/**
 * @brief MainWindow::printFile : appelle la fonction d'impression fichier
 */
void MainWindow::printFile(){
    cout<<"impression"<<endl;
    RDFWidget->print();
}

/**
 * @brief MainWindow::changerColoration
 */
void MainWindow::changerColoration(){

    if (colorationButton->text() == "Avec Couleur"){
        colorationButton->setText("Sans Couleur");
        RDFWidget->changeColoration(0);
    }
    else{
        colorationButton->setText("Avec Couleur");
        RDFWidget->changeColoration(1);
}


}

/**
 * @brief MainWindow::changerMode
 * @param action
 */
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

/**
 * @brief MainWindow::changerPolice
 * @param f
 */
void MainWindow::changerPolice(QFont f){
    RDFWidget->changePolice(f);

}

/**
 * @brief MainWindow::parametrerPourcentagePolice
 * @param rang
 */
void MainWindow::parametrerPourcentagePolice(int rang){
    RDFWidget->changePourcentagePolice(rang +1);

}

/**
 * @brief MainWindow::parametrerPourcentageHPolice
 * @param rang
 */
void MainWindow::parametrerPourcentageHPolice(int rang){
    RDFWidget->changePourcentagePoliceH(rang + 1);

}

/**
 * @brief MainWindow::parametrerTaillePolice
 * @param rang
 */
void MainWindow::parametrerTaillePolice(int rang){
    RDFWidget->changeTaillePolice(rang+1);

}
