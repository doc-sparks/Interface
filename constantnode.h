#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include "processnode.h"
#include "datavalue.h"

class ConstantNode : public ProcessNode
{
private:
    DataValue val_;

public:
    ConstantNode(QVector3D vec, QString name, QObject *parent = 0);

    void setConstValue( DataValue val ) { val_ = val ; }

    virtual void process();
};

#endif // CONSTANTNODE_H
