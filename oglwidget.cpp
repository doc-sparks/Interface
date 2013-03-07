#include "oglwidget.h"
#include <GL/glu.h>
#include <QDebug>
#include <QTimer>

OGLWidget::OGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
     qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
     rtri = 0;
 }

 OGLWidget::~OGLWidget()
 {
 }

 void OGLWidget::initializeGL()
 {

glShadeModel(GL_SMOOTH);
glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
glClearDepth(1.0f);                         // Depth Buffer Setup
glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Test To Do
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
     timer->start(20);
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

     glRotatef(rtri,0.0f,1.0f,0.0f);             // Rotate The Pyramid On It's Y Axis

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
 rtri+=0.2f;

 qDebug() << rtri;
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
