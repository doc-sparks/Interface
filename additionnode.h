#ifndef ADDITIONNODE_H
#define ADDITIONNODE_H

#include "processnode.h"

class AdditionNode : public ProcessNode
{
public:

    AdditionNode(QVector3D vec, QString name, QObject *parent = 0);
    virtual void process();
};


#endif // ADDITIONNODE_H
