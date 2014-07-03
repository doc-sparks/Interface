#include "oglwidget.h"
#include <GL/glu.h>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include "interfacecoreview.h"
#include <math.h>

#define PI 3.14159265

OGLWidget::OGLWidget(InterfaceCoreView *view, QWidget *parent) : QGLWidget(parent),
    parentView_(view), rotValue_(0, 0), posValue_(0, 0, 0), zoomValue_(20.0), mouseLook_(false)
{
    // capture mouse tracking so we can get move events without a button down
    setMouseTracking(true);    

    // must not auto fill background if we're overpainting
    setAutoFillBackground(false);
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
    glClearDepth(1.0f);

    // enable depth testing - required to stop back faces showing through (back face culling)

    // Set up two diffuse lights

    // enable the lighting

    // set the type of depth function
    glDepthFunc(GL_LEQUAL);

    // setup the 'nice' perspective
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // set up the display lists for the nodes
    parentView_->createDisplayLists();

    // set up the timer for a 50Hz view and connect to the update routine
    refreshTimer_ = new QTimer(this);
    connect(refreshTimer_, SIGNAL(timeout()), this, SLOT(mainLoop()));
    refreshTimer_->start(20);
}

void OGLWidget::mainLoop()
{
    // a main loop to do any housekeeping every update

    // update the widget display
    update();

    // check for objects under the mouse pointer
    QPoint p = mapFromGlobal(QCursor::pos());
    parentView_->setHighightedObject( getObjectAtScreenPos(  p.x(), p.y() ) );

    // add a cooldown to slow up/down motion
    static int cooldown = 0;

    // check for keyboard movement
    if (parentView_->isKeyDown(65))  // A
    {
        posValue_.setY( posValue_.y() + (0.15 * sin( PI * rotValue_.x() / 180.0) ) );
        posValue_.setX( posValue_.x() + (0.15 * cos( PI * rotValue_.x() / 180.0) ) );
    }

    if (parentView_->isKeyDown(68))  // D
    {
        posValue_.setY( posValue_.y() - (0.15 * sin( PI * rotValue_.x() / 180.0) ) );
        posValue_.setX( posValue_.x() - (0.15 * cos( PI * rotValue_.x() / 180.0) ) );
    }

    if (parentView_->isKeyDown(87)) // W
    {
        posValue_.setY( posValue_.y() + (0.15 * cos( PI * rotValue_.x() / 180.0) ) );
        posValue_.setX( posValue_.x() - (0.15 * sin( PI * rotValue_.x() / 180.0) ) );
    }

    if (parentView_->isKeyDown(83))  // S
    {
        posValue_.setY( posValue_.y() - (0.15 * cos( PI * rotValue_.x() / 180.0) ) );
        posValue_.setX( posValue_.x() + (0.15 * sin( PI * rotValue_.x() / 180.0) ) );
    }

    // go up/down
    if (cooldown == 0)
    {
        if (parentView_->isKeyDown(81))  // Q
        {
            posValue_.setZ(posValue_.z() + 1.);
            cooldown = 10;
        }

        if (parentView_->isKeyDown(69))  // Q
        {
            posValue_.setZ(posValue_.z() - 1.);
            cooldown = 10;
        }
    } else {
        cooldown -= 1;
    }
}

int OGLWidget::getObjectAtScreenPos(int x, int y)
{
    // set up the selection buffer
    GLuint buffer[512];
    glSelectBuffer(512, buffer);

    // Get the viewport values
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Go into Selection Mode
    glRenderMode(GL_SELECT);
    glInitNames();		// Initializes The Name Stack
    glPushName(-1);		// Push at least one entry

    // go to projection matrix and limit the area around the mouse to be 'drawn'
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();		// Push The Projection Matrix
    glLoadIdentity();	// Resets The Matrix
    gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3]-y), 1.0f, 1.0f, viewport);

    // also set the perspective to ensure the new aspect ratio is correct
    gluPerspective(45.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.1f, 1500.0f);

    // now paint the objects
    glMatrixMode(GL_MODELVIEW);
    parentView_->drawNodes();

    // switch everything back
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // check for hits by switching render mode
    GLint hits=glRenderMode(GL_RENDER);

    // do we have any?
    if (hits > 0)
    {
        // note: selection buffer has 4 values per hit: # of hits at time, min depth, max depth, name

        // start by picking the first hit
        int choose = buffer[3];
        int depth = buffer[1];

        // now loop over the rest
        for (int loop = 1; loop < hits; loop++)
        {
            // is this object closer?
            if (buffer[loop*4+1] < GLuint(depth))
            {
                choose = buffer[loop*4+3];
                depth = buffer[loop*4+1];
            }
        }

        return choose;
    }

    return -1;
}

/*QPointF GLWidget::get3DPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = x;//(float)event->pos().x();
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    double posX, posY, posZ;
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    return QPointF(posX, posZ);
}
*/
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

void OGLWidget::paintEvent(QPaintEvent *)
{
    // reset lighting as overpainting will mess this up
    GLfloat white_light[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light);

    // enable everything again
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHTING);    
    glEnable(GL_DEPTH_TEST);

    // paint the 3D
    paint3D();

    // paint the 2D
    paint2D();
}

void OGLWidget::paint2D()
{
    // set up the painter
    QPainter painter(this);

    // draw the node UI elements
    parentView_->drawNodeUIElements(&painter);

    // draw the fixed UI Elements
    parentView_->drawFixedUIElements(&painter);
}

void OGLWidget::paint3D()
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
    glTranslatef(posValue_.x(), posValue_.z(), posValue_.y());

    // set the light position
    GLfloat light_pos1[]= { 1.0f, 1.0f, 3.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
    GLfloat light_pos2[]= { 1.0f, -1.0f, -3.0f, 0.0f };
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);

    // --------------------------------------------------
    // Now draw each object at the apporpriate positions
    parentView_->drawNodes();

    // And now the data connections
    parentView_->drawConnections();

    // finally draw a grid to help orientate the user
    GLfloat blue[] = {0.0f, .0f, 0.1f, 0.1f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glLineWidth(2.5);
    glBegin(GL_LINES);

    for (int i = -50; i < 50; i++)
    {
        glVertex3f( -50, -posValue_.z(), i );
        glVertex3f( 50, -posValue_.z(), i );
        glVertex3f( i, -posValue_.z(), -50 );
        glVertex3f( i, -posValue_.z(), 50 );
    }

    glEnd();

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
