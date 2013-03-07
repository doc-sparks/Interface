#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "oglwidget.h"
#include "QKeyEvent"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Show the interface fullscreen
    showFullScreen();

    // create and add the openGL Widget
    OGLWidget *w = new OGLWidget();
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
