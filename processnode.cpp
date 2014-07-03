#include "processnode.h"
#include <GL/glu.h>
#include "interfacecoreview.h"
#include "inputdataport.h"
#include "outputdataport.h"
#include <QDebug>
#include "groupuielement.h"
#include "textuielement.h"

ProcessNode::ProcessNode(QVector3D vec, QString name, QObject *parent) :
    QObject(parent),
    displayList_(-1),
    nodeType_("BasicNode"),
    pos_(vec),
    status_(NotReady),
    name_(name),
    uiElement_(NULL),
    uiElementInfo_(NULL)
{
    // add a TextUIElement within a GroupUIElement to show the info
    uiElementInfo_ = new GroupUIElement();
    TextUIElement *header = new TextUIElement();
    header->setText(nodeType_);
    dynamic_cast<GroupUIElement*>(uiElementInfo_)->addElement( header );
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

    // size given by number of inputs/outputs
    double size = getNodeWorldSize();

    // do the drawing
    glBegin(GL_QUADS);

    // main node
    drawCube(size, 1.0, 1.0, QVector3D(0, 0, 0) );

    // input ports
    for (int i = 0; i < inputPorts_.count(); i++)
    {
        drawCube(0.7, 0.2, 0.7, getInputPortPosition(i, true) );
    }

    // output ports
    for (int i = 0; i < outputPorts_.count(); i++)
    {
        //drawCube(0.2, 0.7, 0.2, dx * (i * 2) - size / 2. + dx, -0.5, 0);
        drawCube(0.2, 0.7, 0.2, getOutputPortPosition(i, true));
    }

    glEnd();
}

double ProcessNode::getNodeWorldSize()
{
    double size = ( inputPorts_.count() > outputPorts_.count() ? inputPorts_.count() : outputPorts_.count() );
    if (size < 2) size = 1;
    return size;
}

QVector3D ProcessNode::getOutputPortPosition(int i, bool cube_pos)
{
    // return the base position of the output port
    double size = getNodeWorldSize();
    double dx = size / (outputPorts_.count() * 2);

    // check to return the base cube position or the actual port position
    if (cube_pos)
        return QVector3D(dx * (i * 2) - size / 2. + dx, -0.5, 0);

    return QVector3D(dx * (i * 2) - size / 2. + dx, -0.85, 0);
}

QVector3D ProcessNode::getInputPortPosition(int i, bool cube_pos)
{
    // return the base position of the output port
    double size = getNodeWorldSize();
    double dx = size / (inputPorts_.count() * 2);

    // check to return the base cube position or the actual port position
    if (cube_pos)
        return QVector3D(dx * (i * 2) - size / 2. + dx, 0.5, 0);

    return QVector3D(dx * (i * 2) - size / 2. + dx, 0.6, 0);
}

void ProcessNode::drawCube( double sx, double sy, double sz, QVector3D pos )
{
    sx /= 2.;
    sy /= 2.;
    sz /= 2.;

    glNormal3d(0, 0, 1);
    glVertex3f(  sx + pos.x(), -sy + pos.y(), sz + pos.z() );
    glVertex3f(  sx + pos.x(),  sy + pos.y(), sz + pos.z() );
    glVertex3f( -sx + pos.x(),  sy + pos.y(), sz + pos.z() );
    glVertex3f( -sx + pos.x(), -sy + pos.y(), sz + pos.z() );

    glNormal3d(1, 0, 0);
    glVertex3f( sx + pos.x(), -sy + pos.y(), -sz + pos.z() );
    glVertex3f( sx + pos.x(),  sy + pos.y(), -sz + pos.z() );
    glVertex3f( sx + pos.x(),  sy + pos.y(),  sz + pos.z() );
    glVertex3f( sx + pos.x(), -sy + pos.y(),  sz + pos.z() );

    glNormal3d(-1, 0, 0);
    glVertex3f( -sx + pos.x(), -sy + pos.y(),  sz + pos.z() );
    glVertex3f( -sx + pos.x(),  sy + pos.y(),  sz + pos.z() );
    glVertex3f( -sx + pos.x(),  sy + pos.y(), -sz + pos.z() );
    glVertex3f( -sx + pos.x(), -sy + pos.y(), -sz + pos.z() );

    glNormal3d(0, 1, 0);
    glVertex3f(  sx + pos.x(),  sy + pos.y(),  sz + pos.z() );
    glVertex3f(  sx + pos.x(),  sy + pos.y(), -sz + pos.z() );
    glVertex3f( -sx + pos.x(),  sy + pos.y(), -sz + pos.z() );
    glVertex3f( -sx + pos.x(),  sy + pos.y(),  sz + pos.z() );

    glNormal3d(0, -1, 0);
    glVertex3f(  sx + pos.x(), -sy + pos.y(), -sz + pos.z() );
    glVertex3f(  sx + pos.x(), -sy + pos.y(),  sz + pos.z() );
    glVertex3f( -sx + pos.x(), -sy + pos.y(),  sz + pos.z() );
    glVertex3f( -sx + pos.x(), -sy + pos.y(), -sz + pos.z() );

    glNormal3d(0, 0, -1);
    glVertex3f(  -sx + pos.x(), -sy + pos.y(), -sz + pos.z() );
    glVertex3f(  -sx + pos.x(),  sy + pos.y(), -sz + pos.z() );
    glVertex3f( sx + pos.x(),  sy + pos.y(), -sz + pos.z() );
    glVertex3f( sx + pos.x(), -sy + pos.y(), -sz + pos.z() );
}

int ProcessNode::getPortID(DataPort *p)
{
    // return the index of this port
    int i = inputPorts_.indexOf((InputDataPort*)p);
    if (i != -1)
        return i;

    i = outputPorts_.indexOf((OutputDataPort*)p);
    return i;
}

void ProcessNode::setNodeType(QString t)
{
    nodeType_ = t;
    TextUIElement *h = dynamic_cast<TextUIElement*>( dynamic_cast<GroupUIElement*>(uiElementInfo_)->getElement(0) );
    h->setText(nodeType_);
}
