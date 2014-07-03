#include "splitternode.h"

#include "inputdataport.h"
#include <QDebug>

SplitterNode::SplitterNode(QVector3D vec, QString name, QObject *parent) :
    ProcessNode(vec, name, parent)
{
    setNodeType("SplitterNode");
    addInputPort( new InputDataPort(this) );
}

void SplitterNode::setNumOutputs(int num)
{
    // set the number of outputs
    clearOutputPorts();
    for (int i = 0; i < num; i++ )
    {
        addOutputPort(new OutputDataPort(this));
    }
}

void SplitterNode::process()
{
    // check inputs are OK
    if (getInput(0)->getOutputPort()->getParentNode()->getStatus() == Ready)
    {
        // make ready
        setStatus(Ready);

        // set the outputs
        for (int i = 0; i < outputPorts_.count(); i++)
        {
            getOutput(i)->setValue( getInput(0)->getValue().getDouble() );
        }
    }
}
