#include "interfacecoreapp.h"
#include <QVector3D>
#include <QDebug>
#include <QTimer>

InterfaceCoreApp::InterfaceCoreApp(int & argc, char ** argv) :
    QApplication(argc, argv),
    tickCount_(0), currNode_(0), processing_(false)
{
    // set up the timer for the process ticker
    processTimer_ = new QTimer(this);
    connect(processTimer_, SIGNAL(timeout()), this, SLOT(processTick()));
    processTimer_->start(1000);
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
    if (!processing_)
        return;

    // loop over all nodes and process
    qDebug() << "START PROCESSING LOOP " << tickCount_;

    if (processNodes_[currNode_]->getStatus() == NotReady)
        processNodes_[currNode_]->process();

    currNode_++;
    if (currNode_ == processNodes_.count())
    {
        tickCount_++;
        currNode_ = 0;
    }

}
