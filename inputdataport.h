#ifndef INPUTDATAPORT_H
#define INPUTDATAPORT_H

#include "dataport.h"

class DataValue;
class OutputDataPort;

class InputDataPort : public DataPort
{
private:
    OutputDataPort *outputPort_;

public:
    InputDataPort(ProcessNode *node);

    void connect(OutputDataPort *out);
    DataValue getValue();
    void pushRequest();
    OutputDataPort *getOutputPort();
};

#endif // INPUTDATAPORT_H
