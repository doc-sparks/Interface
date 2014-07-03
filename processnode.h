#ifndef PROCESSNODE_H
#define PROCESSNODE_H

#include <QObject>
#include <QVector3D>
#include <GL/glu.h>
#include <outputdataport.h>
#include "uielement.h"

class InterfaceCoreView;
class InputDataPort;

enum NodeStatus {
    NotReady,
    Processing,
    Ready
};

class ProcessNode : public QObject
{
    Q_OBJECT

private:
    // display list for thie node type
    GLint displayList_;

    // parent view
    InterfaceCoreView *parentView_;

    // defines the node type
    QString nodeType_;

protected:

    // set the node type
    void setNodeType(QString t);

    // node 3d position
    QVector3D pos_;

    // status of this node
    NodeStatus status_;

    // input ports
    QList<InputDataPort*> inputPorts_;

    // output ports
    QList<OutputDataPort*> outputPorts_;

    // name of this node
    QString name_;

    // UI Element if required
    UIElement *uiElement_;

    // Info UI Element that shows stuff about the node
    UIElement *uiElementInfo_;

    // helper function for drawing a cube
    void drawCube( double sx, double sy, double sz, QVector3D pos );
    double getNodeWorldSize();

public:
    explicit ProcessNode(QVector3D vec, QString name, QObject *parent = 0);

    // create the display list
    void draw();

    // return the display list
    GLuint getDisplayList(InterfaceCoreView *view);

    // UI related
    UIElement *getUIElement() { return uiElement_; }
    UIElement *getInfoUIElement() { return uiElementInfo_; }

    // return the node type
    QString getNodeType();

    // port functions
    void addOutputPort( OutputDataPort *d ) { outputPorts_.append(d); }
    void addInputPort( InputDataPort *d ) { inputPorts_.append(d); }
    void clearInputPorts();
    void clearOutputPorts();
    QVector3D getOutputPortPosition(int i, bool cube_pos = false);
    QVector3D getInputPortPosition(int i, bool cube_pos = false);
    int getPortID( DataPort *p );

    // get/set functions
    QVector3D getPos() { return pos_; }
    InputDataPort *getInput( int i );
    OutputDataPort *getOutput( int i );
    void setStatus(NodeStatus s);
    NodeStatus getStatus() { return status_; }
    int getNumInputPorts() { return inputPorts_.count(); }
    int getNumOutputPorts() { return outputPorts_.count(); }

    // processing
    virtual void process();
    virtual void processPushRequest(InputDataPort *port);

signals:
    
public slots:
    
};

#endif // PROCESSNODE_H
