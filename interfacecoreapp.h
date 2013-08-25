#ifndef INTERFACECOREAPP_H
#define INTERFACECOREAPP_H

#include <QApplication>
#include "processnode.h"

class InterfaceCoreApp : public QApplication
{
    Q_OBJECT

private:
    QList<ProcessNode*> processNodes_;
    int tickCount_;

public:
    explicit InterfaceCoreApp(int & argc, char ** argv);
    
    void addNode( ProcessNode *node );
    int getProcessNodeCount();
    ProcessNode *getProcessNode( int i );
    void processTick();
    void initialiseNodes();

signals:
    
public slots:
    
};

#endif // INTERFACECOREAPP_H
