#include "additionnode.h"
#include "inputdataport.h"
#include <QDebug>

AdditionNode::AdditionNode(QVector3D vec, QString name, QObject *parent) :
    ProcessNode(vec, name, parent)
{
    setNodeType("AdditionNode");

    // two inputs, one output
    addInputPort(new InputDataPort(this));
    addInputPort(new InputDataPort(this));
    addOutputPort( new OutputDataPort(this) );
}

void AdditionNode::process()
{
    // check inputs are OK
    if ((getInput(0)->getOutputPort()->getParentNode()->getStatus() == Ready) &&
        (getInput(1)->getOutputPort()->getParentNode()->getStatus() == Ready))
    {
        // perform addition
        getOutput(0)->setValue( getInput(0)->getValue().getDouble() + getInput(1)->getValue().getDouble() );

        // set ready
        setStatus(Ready);
    }
}
