#include "inputdataport.h"
#include "outputdataport.h"
#include "processnode.h"

InputDataPort::InputDataPort(ProcessNode *node) :
    DataPort(node),
    outputPort_(NULL)
{
}

void InputDataPort::connect(OutputDataPort *out)
{
    outputPort_ = out;
}

OutputDataPort *InputDataPort::getOutputPort()
{
    return outputPort_;
}

DataValue InputDataPort::getValue()
{
    return outputPort_->pullRequest();
}

void InputDataPort::pushRequest()
{
    // set connected node to NotReady
    parentNode_->processPushRequest(this);
}
