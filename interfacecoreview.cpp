#include "interfacecoreview.h"
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
    app_(app),
    highlightedObject_(-1),
    selectedObject_(-1),
    oglWidget_(NULL)
{
    // Show the interface fullscreen
    showFullScreen();

    // create and add the openGL Widget
    OGLWidget *w = new OGLWidget(this);
    setCentralWidget(w);
    oglWidget_ = w;
}

InterfaceCoreView::~InterfaceCoreView()
{

}

void InterfaceCoreView::mousePressEvent(QMouseEvent *event)
{
    // check for left mouse click
    if (event->buttons() != Qt::LeftButton)
    {
        return;
    }

    // select a node
    if (highlightedObject_ != -1)
    {
        selectedObject_ = highlightedObject_;
    }
    else
    {
        selectedObject_ = -1;
    }
}

void InterfaceCoreView::mouseDoubleClickEvent(QMouseEvent *event)
{
    // check for double click on nodes
    if (highlightedObject_ != -1)
    {
        // focus view on node
        QVector3D new_pos;
        new_pos.setX( -app_->getProcessNode(highlightedObject_)->getPos().x() );
        new_pos.setY( app_->getProcessNode(highlightedObject_)->getPos().z() );
        new_pos.setZ( -app_->getProcessNode(highlightedObject_)->getPos().y() );
        oglWidget_->setPosition( new_pos );
    }
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
    // go through the node types and draw the node
    for (int i = 0; i < app_->getProcessNodeCount(); i++ )
    {
        // store the camera-relative world position
        glPushMatrix();

        ProcessNode *n = app_->getProcessNode(i);

        // shift to node position
        glTranslatef( n->getPos().x(), n->getPos().y(), n->getPos().z() );

        // push the object id
        glLoadName( i );

        // set the colour depending on status
        if (selectedObject_ == i)
        {
            GLfloat yellow[] = {0.8f, .8f, .2f, 1.f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
        } else if (highlightedObject_ == i)
        {
            GLfloat blue[] = {0.2f, .2f, .8f, 1.f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
        } else if (n->getStatus() == NotReady)
        {
            GLfloat red[] = {0.8f, .2f, .2f, 1.f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
        } else if (n->getStatus() == Ready)
        {
            GLfloat green[] = {0.2f, .8f, .2f, 1.f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
        }

        // draw the node - remove display lists at present as some nodes are dynamic
        //glCallList(n->getDisplayList(this));
        n->draw();

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
            int k = n->getOutput(j)->getInputPort()->getID();
            QVector3D in_pos = m->getPos() + m->getInputPortPosition(k);
            QVector3D out_pos = n->getPos() + n->getOutputPortPosition(j);


            GLfloat red[] = {1.0f, .0f, 0.f, 1.f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
            glLineWidth(2.5);
            glBegin(GL_LINES);

            glVertex3f( n->getOutputPortPosition(j).x(), n->getOutputPortPosition(j).y(), n->getOutputPortPosition(j).z() );
            glVertex3f( in_pos.x() - n->getPos().x(), in_pos.y() - n->getPos().y(), in_pos.z() - n->getPos().z() );


            glEnd();
        }

        // restore the world position after object draw
        glPopMatrix();
    }
}

void InterfaceCoreView::drawNodeUIElements(QPainter *p)
{
    // go through the node types and draw any UI Elements
    for (int i = 0; i < app_->getProcessNodeCount(); i++ )
    {
        // check if a node has a UI Element and draw it
        //  - The UI element (controlled by the view) knows where it is and how to draw itself
        ProcessNode *n = app_->getProcessNode(i);
        if (n->getUIElement())
        {
            n->getUIElement()->paint(p);
        }
    }

    // draw info UI elements
    if (selectedObject_ != -1)
    {
        app_->getProcessNode(selectedObject_)->getInfoUIElement()->paint(p);
    }
}

void InterfaceCoreView::drawFixedUIElements(QPainter *p)
{
    // go through the fixed UI Eleemnts and draw them
    for (int i = 0; i < fixedUIElements_.count(); i++ )
    {
        fixedUIElements_.at(i)->paint(p);
    }
}

GLuint InterfaceCoreView::getDisplayList( QString node_type )
{
    // return the display list for this node type
    if (!displayListMap_.contains( node_type ))
        return -1;

    return displayListMap_[ node_type ];
}
