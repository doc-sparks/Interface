#ifndef MERGERNODE_H
#define MERGERNODE_H

#include "processnode.h"

class MergerNode : public ProcessNode
{
public:
    // mode for the merger
    enum Mode {
        Priority,
        LastPush
    };

    MergerNode(QVector3D vec, QString name, QObject *parent = 0);
    virtual void process();
    void setOutputMode( MergerNode::Mode mode );
    void setNumInputs( int num );

    virtual void processPushRequest( InputDataPort *port );

private:
    MergerNode::Mode mode_;
    InputDataPort *activePort_;
};

#endif // MERGERNODE_H
