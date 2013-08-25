#include "interfacecoreapp.h"
#include <QVector3D>
#include <QDebug>

InterfaceCoreApp::InterfaceCoreApp(int & argc, char ** argv) :
    QApplication(argc, argv),
    tickCount_(0)
{    
}

void InterfaceCoreApp::addNode( ProcessNode *node )
{
    // add the given node to the list
    processNodes_.append( node );
}

int InterfaceCoreApp::getProcessNodeCount()
{
   return processNodes_.count();
}

ProcessNode *InterfaceCoreApp::getProcessNode( int i )
{
    return processNodes_[i];
}

void InterfaceCoreApp::initialiseNodes( )
{
    // initialise all the nodes

    // set everything to Not Ready
    for (int i = 0; i < processNodes_.count(); i++)
    {
        processNodes_[i]->setStatus(NotReady);
    }
}

void InterfaceCoreApp::processTick( )
{
    // loop over all nodes and process
    qDebug() << "START PROCESSING LOOP " << tickCount_;
    for (int i = 0; i < processNodes_.count(); i++)
    {        
        if (processNodes_[i]->getStatus() == NotReady)
            processNodes_[i]->process();
    }

    tickCount_++;
}
