#include "stdoutnode.h"
#include "inputdataport.h"
#include <QDebug>

StdOutNode::StdOutNode(QVector3D vec, QString name, QObject *parent) :
    ProcessNode(vec, name, parent)
{
    nodeType_ = "StdOutNode";
    addInputPort(new InputDataPort(this));
}

void StdOutNode::process()
{
    // check inputs are OK
    if (getInput(0)->getOutputPort()->getParentNode()->getStatus() == Ready)
    {
        // make ready
        setStatus(Ready);

        // and output the value
        qDebug() << "STDOUT>  " << getInput(0)->getValue().getString();
    }
}
