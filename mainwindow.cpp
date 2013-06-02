#include "mainwindow.h"
#include "oglwidget.h"
#include "QKeyEvent"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Show the interface fullscreen
    showFullScreen();

    // create and add the openGL Widget
    OGLWidget *w = new OGLWidget(this);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    // if we're quitting, then fine
    if (e->key() == Qt::Key_Escape)
    {
        close();
        return;
    }

    // otherwise update the keyboard map
    keyboardMap_[ e->key() ] = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    // update the keyboard map
    keyboardMap_[ e->key() ] = false;
}

bool MainWindow::isKeyDown(int key)
{
    // check in the map to see if the key is down
    if (keyboardMap_.contains(key))
        return keyboardMap_[ key ];
    else
        return false;
}
