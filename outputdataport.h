#ifndef OUTPUTDATAPORT_H
#define OUTPUTDATAPORT_H

#include "dataport.h"
#include "datavalue.h"

class InputDataPort;

class OutputDataPort : public DataPort
{
private:
    InputDataPort *inputPort_;
    DataValue value_;

public:
    OutputDataPort(ProcessNode *node);

    // connect to an input port
    void connect( InputDataPort *in );

    // set the value
    void setValue(DataValue val);

    DataValue pullRequest();

    InputDataPort *getInputPort();
};

#endif // OUTPUTDATAPORT_H
