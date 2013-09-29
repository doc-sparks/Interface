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
    int currNode_;
    bool processing_;
    QTimer *processTimer_;

public:
    explicit InterfaceCoreApp(int & argc, char ** argv);
    
    void addNode( ProcessNode *node );
    int getProcessNodeCount();
    ProcessNode *getProcessNode( int i );    
    void initialiseNodes();

    void startProcessing() { processing_ = true; }
    void stopProcessing() { processing_ = false; }
    bool isProcessing() { return processing_; }

signals:
    
public slots:
    void processTick();
};

#endif // INTERFACECOREAPP_H
