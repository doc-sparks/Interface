#include "interfacecoreview.h"
#include "oglwidget.h"
#include "QKeyEvent"
#include "additionnode.h"
#include "constantnode.h"
#include "splitternode.h"
#include "stdoutnode.h"
#include "mergernode.h"
#include "stdoutnode.h"
#include "inputdataport.h"

InterfaceCoreView::InterfaceCoreView(InterfaceCoreApp *app, QWidget *parent) :
    QMainWindow(parent),
    app_(app)
{
    // Show the interface fullscreen
    showFullScreen();

    // create and add the openGL Widget
    OGLWidget *w = new OGLWidget(this);
    setCentralWidget(w);
}

InterfaceCoreView::~InterfaceCoreView()
{

}

void InterfaceCoreView::keyPressEvent(QKeyEvent *e)
{
    // if we're quitting, then fine
    if (e->key() == Qt::Key_Escape)
    {
        close();
        return;
    }

    // check for program step
    if (e->key() == Qt::Key_Space)
    {
        if (app_->isProcessing())
            app_->stopProcessing();
        else
            app_->startProcessing();
        return;
    }

    // otherwise update the keyboard map
    keyboardMap_[ e->key() ] = true;
}

void InterfaceCoreView::keyReleaseEvent(QKeyEvent *e)
{
    // update the keyboard map
    keyboardMap_[ e->key() ] = false;
}

bool InterfaceCoreView::isKeyDown(int key)
{
    // check in the map to see if the key is down
    if (keyboardMap_.contains(key))
        return keyboardMap_[ key ];
    else
        return false;
}

void InterfaceCoreView::createDisplayLists()
{
    // create an array of all the nodes
    QList<ProcessNode*> all_nodes;
    all_nodes.append( new ProcessNode( QVector3D(0, 0, 0), "TestNode1" ) );
    all_nodes.append( new AdditionNode( QVector3D(0, 0, 0), "TestNode2" ) );
    all_nodes.append( new ConstantNode( QVector3D(0, 0, 0), "TestNode3" ) );
    all_nodes.append( new MergerNode( QVector3D(0, 0, 0), "TestNode4" ) );
    all_nodes.append( new SplitterNode( QVector3D(0, 0, 0), "TestNode5" ) );
    all_nodes.append( new StdOutNode( QVector3D(0, 0, 0), "TestNode6" ) );

    // reserve the number of display lists
    GLuint display_lists = glGenLists(all_nodes.count());

    // go through the node types and create the display lists
    for (int i = 0; i < all_nodes.count(); i++ )
    {
        // set the new list
        glNewList(display_lists + i, GL_COMPILE);

        // have the node run the OpenGL commands
        all_nodes[i]->draw();

        // finish off the list
        glEndList();

        // set it into the map
        displayListMap_[ all_nodes[i]->getNodeType() ] = display_lists + i;
    }

    // delete the nodes
    for (int i = 0; i < all_nodes.count(); i++ )
    {
        delete all_nodes[i];
    }
}

void InterfaceCoreView::drawNodes()
{
    // go through the node types and create the display lists
    for (int i = 0; i < app_->getProcessNodeCount(); i++ )
    {
        // store the camera-relative world position
        glPushMatrix();

        // shift to node position
        ProcessNode *n = app_->getProcessNode(i);
        glTranslatef( n->getPos().x(), n->getPos().y(), n->getPos().z() );

        // set the colour depending on status
        if (n->getStatus() == NotReady)
        {
            GLfloat red[] = {0.8f, .2f, .2f, 1.f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
        } else if (n->getStatus() == Ready)
        {
            GLfloat green[] = {0.2f, .8f, .2f, 1.f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
        }

        // draw the node
        glCallList(n->getDisplayList(this));

        // restore the world position after object draw
        glPopMatrix();
    }
}

void InterfaceCoreView::drawConnections()
{
    // go through the node types and create the display lists
    for (int i = 0; i < app_->getProcessNodeCount(); i++ )
    {
        // store the camera-relative world position
        glPushMatrix();

        // shift to primary node position
        ProcessNode *n = app_->getProcessNode(i);
        glTranslatef( n->getPos().x(), n->getPos().y(), n->getPos().z() );

        // draw the connection for all outputs
        for (int j = 0; j < n->getNumOutputPorts(); j++)
        {
            // is the output connected?
            if (!n->getOutput(j)->getInputPort())
                continue;

            // yes - so draw the connection
            ProcessNode *m = n->getOutput(j)->getInputPort()->getParentNode();

            glBegin(GL_QUADS);

            // front face
            glColor3f(   1.0,  0.0, 0.0 );
            glVertex3f(  0, -0.05, 0 );
            glVertex3f(  0,  0.05, 0 );
            glVertex3f( m->getPos().x() - n->getPos().x(), m->getPos().y() + 0.05 - n->getPos().y(), m->getPos().z() - n->getPos().z() );
            glVertex3f( m->getPos().x() - n->getPos().x(), m->getPos().y() - 0.05 - n->getPos().y(), m->getPos().z() - n->getPos().z() );

            // back face
            glColor3f(   1.0,  0.0, 0.0 );
            glVertex3f(  0, -0.05, 0 );
            glVertex3f( m->getPos().x() - n->getPos().x(), m->getPos().y() - 0.05 - n->getPos().y(), m->getPos().z() - n->getPos().z() );
            glVertex3f( m->getPos().x() - n->getPos().x(), m->getPos().y() + 0.05 - n->getPos().y(), m->getPos().z() - n->getPos().z() );
            glVertex3f(  0, 0.05, 0 );

            glEnd();
        }

        // restore the world position after object draw
        glPopMatrix();
    }
}

GLuint InterfaceCoreView::getDisplayList( QString node_type )
{
    // return the display list for this node type
    if (!displayListMap_.contains( node_type ))
        return -1;

    return displayListMap_[ node_type ];
}
