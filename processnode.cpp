#include "processnode.h"
#include <GL/glu.h>
#include "interfacecoreview.h"
#include "inputdataport.h"
#include "outputdataport.h"
#include <QDebug>

ProcessNode::ProcessNode(QVector3D vec, QString name, QObject *parent) :
    QObject(parent),
    displayList_(-1),
    nodeType_("BasicNode"),
    pos_(vec),
    status_(NotReady),
    name_(name)
{

}

void ProcessNode::clearInputPorts()
{
    // delete all the input ports connected - TODO: check for other uses - BAD POINTERS AHOY!
    for (int i = 0; i < inputPorts_.count(); i++)
    {
        delete inputPorts_[i];
    }

    inputPorts_.clear();

}

void ProcessNode::clearOutputPorts()
{
    // delete all the input ports connected - TODO: check for other uses - BAD POINTERS AHOY!
    for (int i = 0; i < outputPorts_.count(); i++)
    {
        delete outputPorts_[i];
    }

    outputPorts_.clear();

}

QString ProcessNode::getNodeType()
{
    return nodeType_;
}

GLuint ProcessNode::getDisplayList(InterfaceCoreView *view)
{
    if (displayList_ == -1)
    {
        // get the display list as we haven't cached it
        GLuint dl = view->getDisplayList( getNodeType() );
        displayList_ = dl;
    }

    return displayList_;
}

InputDataPort *ProcessNode::getInput( int i )
{
    return inputPorts_.at(i);
}

OutputDataPort *ProcessNode::getOutput( int i )
{
    return outputPorts_.at(i);
}

void ProcessNode::process(  )
{
    qDebug() << name_ << ": process Called";

    setStatus(Ready);
}

void ProcessNode::processPushRequest( InputDataPort *port )
{
    Q_UNUSED(port);
    qDebug() << name_ << ": processing Push Request";

    // by default, just change to not ready as data has changed
    if (status_ == Ready)
    {
        setStatus( NotReady );
    }
}


void ProcessNode::setStatus(NodeStatus s)
{
    QString str;

    switch (s)
    {
        case Ready:
        str = "Ready";
        break;

        case NotReady:
        str = "NotReady";
        break;

        case Processing:
        str = "Processing";
        break;
    }

    qDebug() << name_ << ": setting status to " << str;
    status_ = s;
}

void ProcessNode::draw()
{
    // a basic cube for a basic node
    glBegin(GL_QUADS);

    glNormal3d(0, 0, 1);
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );

    glNormal3d(1, 0, 0);
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );

    glNormal3d(-1, 0, 0);
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );

    glNormal3d(0, 1, 0);
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );

    glNormal3d(0, -1, 0);
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );

    glNormal3d(0, 0, -1);
    glVertex3f(  -0.5, -0.5, -0.5 );
    glVertex3f(  -0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5, -0.5, -0.5 );

    glEnd();
}
