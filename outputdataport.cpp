#include "outputdataport.h"
#include "inputdataport.h"

OutputDataPort::OutputDataPort(ProcessNode *node) :
    DataPort(node),
    inputPort_(NULL),
    value_(0)
{
}

void OutputDataPort::connect(InputDataPort *in)
{
    inputPort_ = in;
}

void OutputDataPort::setValue(DataValue val)
{
    // check if we should trigger a push
    if (val != value_)
    {
        value_ = val;
        inputPort_->pushRequest();
    }
}

DataValue OutputDataPort::pullRequest()
{
    return value_;
}
