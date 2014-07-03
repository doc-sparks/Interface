#include "stdoutnode.h"
#include "inputdataport.h"
#include "groupuielement.h"

#include <QDebug>

StdOutNode::StdOutNode(QVector3D vec, QString name, QObject *parent) :
    ProcessNode(vec, name, parent)
{
    setNodeType("StdOutNode");
    addInputPort(new InputDataPort(this));

    // add a TextUIElement within a GroupUIElement to show the output
    groupUI_ = new GroupUIElement();
    outUI_ = new TextUIElement();
    headerUI_ = new TextUIElement();
    headerUI_->setText("Output:");

    uiElement_ = groupUI_;
    //groupUI_->setVerticalStyle();
    groupUI_->addElement( headerUI_ );
    groupUI_->addElement( outUI_ );
}

void StdOutNode::process()
{
    // check inputs are OK
    if (getInput(0)->getOutputPort()->getParentNode()->getStatus() == Ready)
    {
        // make ready
        setStatus(Ready);

        // and output the value to the UI Element
        outUI_->setText(getInput(0)->getValue().getString());
    }
}

