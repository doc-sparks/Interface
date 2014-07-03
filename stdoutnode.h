#ifndef STDOUTNODE_H
#define STDOUTNODE_H

#include "processnode.h"
#include "groupuielement.h"
#include "textuielement.h"

class StdOutNode : public ProcessNode
{
public:
    StdOutNode(QVector3D vec, QString name, QObject *parent = 0);
    virtual void process();

private:
    GroupUIElement *groupUI_;
    TextUIElement *outUI_;
    TextUIElement *headerUI_;
};

#endif // STDOUTNODE_H
