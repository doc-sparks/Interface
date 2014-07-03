#include "constantnode.h"
#include "outputdataport.h"

ConstantNode::ConstantNode(QVector3D vec, QString name, QObject *parent) :
    ProcessNode(vec, name, parent)
{
    setNodeType("ConstantNode");
    val_.setValue(0.0);

    addOutputPort( new OutputDataPort(this) );
    getOutput(0)->setValue(val_);
}

void ConstantNode::process()
{
    // make ready
    setStatus(Ready);

    // and push the value
    getOutput(0)->setValue(val_);
}
