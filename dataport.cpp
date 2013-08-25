#include "dataport.h"
#include "inputdataport.h"
#include "outputdataport.h"

//void DataPort::connect(OutputPort *oport, InputPort *iport);

DataPort::DataPort(ProcessNode *node, QObject *parent) :
    QObject(parent),
    parentNode_(node)
{
}

void DataPort::connect(OutputDataPort *oport, InputDataPort *iport)
{
    oport->connect( iport );
    iport->connect( oport );
}
