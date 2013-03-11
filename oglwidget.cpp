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
    glViewport(0, 0, width, height);                    // Reset The Current Viewport
    glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
    glLoadIdentity();                           // Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
    glLoadIdentity();
}



 void OGLWidget::paintGL()
 {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
     glLoadIdentity();                   // Reset The View
     glTranslatef(-1.5f,0.0f,-6.0f);             // Move Left And Into The Screen

     glRotatef(rotValue_,0.0f,1.0f,0.0f);             // Rotate The Pyramid On It's Y Axis

     glBegin(GL_TRIANGLES);

     glColor3f(1.0f,0.0f,0.0f);          // Red
     glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Front)
     glColor3f(0.0f,1.0f,0.0f);          // Green
     glVertex3f(-1.0f,-1.0f, 1.0f);          // Left Of Triangle (Front)
     glColor3f(0.0f,0.0f,1.0f);          // Blue
     glVertex3f( 1.0f,-1.0f, 1.0f);          // Right Of Triangle (Front)

     glColor3f(1.0f,0.0f,0.0f);          // Red
     glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Right)
     glColor3f(0.0f,0.0f,1.0f);          // Blue
     glVertex3f( 1.0f,-1.0f, 1.0f);          // Left Of Triangle (Right)
     glColor3f(0.0f,1.0f,0.0f);          // Green
     glVertex3f( 1.0f,-1.0f, -1.0f);         // Right Of Triangle (Right)

     glColor3f(1.0f,0.0f,0.0f);          // Red
     glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Back)
     glColor3f(0.0f,1.0f,0.0f);          // Green
     glVertex3f( 1.0f,-1.0f, -1.0f);         // Left Of Triangle (Back)
     glColor3f(0.0f,0.0f,1.0f);          // Blue
     glVertex3f(-1.0f,-1.0f, -1.0f);         // Right Of Triangle (Back)

     glColor3f(1.0f,0.0f,0.0f);          // Red
     glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Left)
     glColor3f(0.0f,0.0f,1.0f);          // Blue
     glVertex3f(-1.0f,-1.0f,-1.0f);          // Left Of Triangle (Left)
     glColor3f(0.0f,1.0f,0.0f);          // Green
     glVertex3f(-1.0f,-1.0f, 1.0f);          // Right Of Triangle (Left)
 glEnd();                        // Done Drawing The Pyramid
 rotValue_+=0.2f;
 }


 void OGLWidget::mousePressEvent(QMouseEvent *event)
 {
 //    lastPos = event->pos();
 }

 void OGLWidget::mouseMoveEvent(QMouseEvent *event)
 {
   /*  int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 8 * dy);
         setYRotation(yRot + 8 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         setXRotation(xRot + 8 * dy);
         setZRotation(zRot + 8 * dx);
     }
     lastPos = event->pos();*/
 }
