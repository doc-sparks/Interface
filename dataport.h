#ifndef DATAPORT_H
#define DATAPORT_H

#include <QObject>
class ProcessNode;
class InputDataPort;
class OutputDataPort;

class DataPort : public QObject
{
    Q_OBJECT

protected:
    ProcessNode *parentNode_;

public:
    explicit DataPort(ProcessNode *node, QObject *parent = 0);

    void setParentNode(ProcessNode *node) { parentNode_ = node; }
    ProcessNode *getParentNode() { return parentNode_; }
    int getID();

    static void connect( OutputDataPort *oport, InputDataPort *iport );

signals:
    
public slots:
    
};

#endif // DATAPORT_H
