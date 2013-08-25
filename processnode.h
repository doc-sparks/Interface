#ifndef PROCESSNODE_H
#define PROCESSNODE_H

#include <QObject>
#include <QVector3D>
#include <GL/glu.h>
#include <outputdataport.h>

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

protected:

    // node type - defined for each in constructor
    QString nodeType_;

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

public:
    explicit ProcessNode(QVector3D vec, QString name, QObject *parent = 0);

    // create the display list
    void draw();

    // return the display list
    GLuint getDisplayList(InterfaceCoreView *view);

    // return the node type
    QString getNodeType();

    // port functions
    void addOutputPort( OutputDataPort *d ) { outputPorts_.append(d); }
    void addInputPort( InputDataPort *d ) { inputPorts_.append(d); }

    // get/set functions
    QVector3D getPos() { return pos_; }
    InputDataPort *getInput( int i );
    OutputDataPort *getOutput( int i );
    void setStatus(NodeStatus s);
    NodeStatus getStatus() { return status_; }

    // processing
    virtual void process();
    virtual void processPushRequest(InputDataPort *port);

signals:
    
public slots:
    
};

#endif // PROCESSNODE_H
