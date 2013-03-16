#include "oglwidget.h"
#include <GL/glu.h>
#include <QDebug>
#include <QTimer>

OGLWidget::OGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    rotValue_ = 0;
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::initializeGL()
{
    // set smoothing
    //glShadeModel(GL_SMOOTH);

    // clear a black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
    connect(refreshTimer_, SIGNAL(timeout()), this, SLOT(updateGL()));
    refreshTimer_->start(20);
}

void OGLWidget::resizeGL(int width, int height)
{
    // Set the viewport given the resize event
    glViewport(0, 0, width, height);

    // Reset the Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window and set the perspective
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    // Reset the Model View matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::paintGL()
{
    // cler the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // reset the view to the identity
    glLoadIdentity();

    // move into the screen
    glTranslatef(0.0f, 0.0f, -6.0f);

    // rotate the cube by the rotation value
    glRotatef(rotValue_, 0.0f, 1.0f, 0.0f);

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

    // finally, update the rotation
    rotValue_ += 0.2f;
}


void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    // trigger on mouse press
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // trigger on mouse move
}
