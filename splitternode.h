#ifndef SPLITTERNODE_H
#define SPLITTERNODE_H

#include "processnode.h"

class SplitterNode : public ProcessNode
{
public:

    SplitterNode (QVector3D vec, QString name, QObject *parent = 0);
    virtual void process();
    void setNumOutputs( int num );
};

#endif // SPLITTERNODE_H
