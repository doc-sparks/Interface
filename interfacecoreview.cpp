#include "interfacecoreview.h"
#include "oglwidget.h"
#include "QKeyEvent"

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
    all_nodes.append( new ProcessNode( QVector3D(0, 0, 0) ) );

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

        // draw the node
        glCallList(n->getDisplayList(this));

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
