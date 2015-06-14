#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "visurdfwidget.h"
#include "visurdfdessinateur.h"
#include "QToolBar"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    visuRDFWidget * RDFWidget;

public slots:
    void openFile();
    void printFile();
    void quitApp();
};

#endif // MAINWINDOW_H
