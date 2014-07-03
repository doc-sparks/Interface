#include "mergernode.h"

#include "inputdataport.h"
#include <QDebug>

MergerNode::MergerNode(QVector3D vec, QString name, QObject *parent) :
    ProcessNode(vec, name, parent)
{
    setNodeType("MergerNode");
    addOutputPort( new OutputDataPort(this) );
    mode_ = LastPush;
    activePort_ = NULL;
}

void MergerNode::setOutputMode( MergerNode::Mode mode )
{
    mode_ = mode;
}

void MergerNode::setNumInputs(int num)
{
    // set the number of inputs
    clearInputPorts();
    for (int i = 0; i < num; i++ )
    {
        addInputPort(new InputDataPort(this));
    }
}

void MergerNode::processPushRequest( InputDataPort *port )
{
    // check which port has pushed and if we should respond
    qDebug() << name_ << ": processing Push Request";

    // by default, just change to not ready as data has changed
    switch (mode_)
    {
    case Priority:
        // only set to not ready if 'no other 'higher order' port is ready
        for (int i = 0; i < inputPorts_.count(); i++)
        {
            if (inputPorts_.at(i) == port)
            {
                activePort_ = port;
                break;
            } else if (inputPorts_.at(i)->getOutputPort()->getParentNode()->getStatus() == Ready)
            {
                // a higher priority port is Ready so we don't care
                return;
            }
        }
        break;

    case LastPush:
        // record the last push port
        activePort_ = port;
        break;
    }

    if (status_ == Ready)
    {
        setStatus( NotReady );
    }
}

void MergerNode::process()
{
    // check we have at least one port ready
    if ((activePort_) && (activePort_->getOutputPort()->getParentNode()->getStatus() == Ready))
    {
        // set the output
        getOutput(0)->setValue( activePort_->getValue().getDouble() );

        // make ready
        setStatus(Ready);
    }
}
