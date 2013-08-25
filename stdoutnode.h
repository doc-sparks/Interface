#ifndef STDOUTNODE_H
#define STDOUTNODE_H

#include "processnode.h"

class StdOutNode : public ProcessNode
{
public:
    StdOutNode(QVector3D vec, QString name, QObject *parent = 0);
    virtual void process();
};

#endif // STDOUTNODE_H
