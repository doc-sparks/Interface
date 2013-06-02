#include "oglwidget.h"
#include <GL/glu.h>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include "mainwindow.h"
#include <math.h>

#define PI 3.14159265

OGLWidget::OGLWidget(MainWindow *win, QWidget *parent) : QGLWidget(parent),
    parentWin_(win), rotValue_(0, 0), posValue_(0, 0), zoomValue_(6.0), mouseLook_(false)
{
    // capture mouse tracking so we can get move events without a button down
    setMouseTracking(true);    
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::initializeGL()
{
    // set smoothing
    //glShadeModel(GL_SMOOTH);

    // clear a black background
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // clear the depth buffer
    //glClearDepth(1.0f);

    // enable depth testing - required to stop back faces showing through (back face culling)
    glEnable(GL_DEPTH_TEST);

    // set the type of depth function
    //glDepthFunc(GL_LEQUAL);

    // setup the 'nice' perspective
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // set up the timer for a 50Hz view and connect to the update routine
    refreshTimer_ = new QTimer(this);
    connect(refreshTimer_, SIGNAL(timeout()), this, SLOT(mainLoop()));
    refreshTimer_->start(20);
}

void OGLWidget::mainLoop()
{
    // a main loop to do any housekeeping every update

    // check for keyboard movement
    if (parentWin_->isKeyDown(65))  // A
    {
        posValue_.setY( posValue_.y() + (0.05 * sin( PI * rotValue_.x() / 180.0) ) );
        posValue_.setX( posValue_.x() + (0.05 * cos( PI * rotValue_.x() / 180.0) ) );
    }

    if (parentWin_->isKeyDown(68))  // D
    {
        posValue_.setY( posValue_.y() - (0.05 * sin( PI * rotValue_.x() / 180.0) ) );
        posValue_.setX( posValue_.x() - (0.05 * cos( PI * rotValue_.x() / 180.0) ) );
    }

    if (parentWin_->isKeyDown(87)) // W
    {
        posValue_.setY( posValue_.y() + (0.05 * cos( PI * rotValue_.x() / 180.0) ) );
        posValue_.setX( posValue_.x() - (0.05 * sin( PI * rotValue_.x() / 180.0) ) );
    }

    if (parentWin_->isKeyDown(83))  // S
    {
        posValue_.setY( posValue_.y() - (0.05 * cos( PI * rotValue_.x() / 180.0) ) );
        posValue_.setX( posValue_.x() + (0.05 * sin( PI * rotValue_.x() / 180.0) ) );
    }

    // update the widget display
    updateGL();
}

void OGLWidget::resizeGL(int width, int height)
{
    // Set the viewport given the resize event
    glViewport(0, 0, width, height);

    // Reset the Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window and set the perspective
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

    // Reset the Model View matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();    
}

void OGLWidget::paintGL()
{
    // cler the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --------------------------------------------------
    // set up the camera view

    // reset the view to the identity
    glLoadIdentity();

    // move everything back by the zoom factor
    glTranslatef(0.0f, 0.0f, -zoomValue_);

    // rotate everything
    glRotatef(rotValue_.y(), 1.0f, 0.0f, 0.0f);
    glRotatef(rotValue_.x(), 0.0f, 1.0f, 0.0f);

    // finally offset by the current viewing point
    glTranslatef(posValue_.x(), 0.0f, posValue_.y());

    // --------------------------------------------------
    // Now draw each object and the apporpriate positions

    // store the camera-relative world position
    glPushMatrix();

    // construct the cube
    glBegin(GL_QUADS);

    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );

    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );

    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );

    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );

    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );

    glColor3f(   1.0,  1.0, 0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );

    glEnd();

    // restore the world position after object draw
    glPopMatrix();
}

void OGLWidget::wheelEvent(QWheelEvent *event)
{
    // zoom in and out with the mouse wheel
    zoomValue_ -= event->delta() / 200.0;

    // apply limits
    if (zoomValue_ < 1.0)
        zoomValue_ = 1.0;

    if (zoomValue_ > 30.0)
        zoomValue_ = 30.0;

}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // is the middle mouse button down?
    if (event->buttons() == Qt::MidButton)
    {
        // was it already down? If not, store the current coords
        if (!mouseLook_)
        {
            tmpMousePos_ = event->pos();
            tmpRotValue_ = rotValue_;
            mouseLook_ = true;
        }

        // update the rotation values depending on the relative mouse position
        rotValue_.setX( tmpRotValue_.x() + (tmpMousePos_.x() - event->pos().x()) * 0.2 );
        rotValue_.setY( tmpRotValue_.y() + (tmpMousePos_.y() - event->pos().y()) * -0.2 );
    }
    else
    {
        // turn off mouse look
        mouseLook_ = false;
    }

}
