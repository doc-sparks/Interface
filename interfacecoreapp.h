#ifndef INTERFACECOREAPP_H
#define INTERFACECOREAPP_H

#include <QApplication>
#include "processnode.h"

class InterfaceCoreApp : public QApplication
{
    Q_OBJECT

private:
    QList<ProcessNode*> processNodes_;

public:
    explicit InterfaceCoreApp(int & argc, char ** argv);
    
    void addNode( ProcessNode *node );

signals:
    
public slots:
    
};

#endif // INTERFACECOREAPP_H
