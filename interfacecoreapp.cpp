#include "interfacecoreapp.h"
#include <QVector3D>

InterfaceCoreApp::InterfaceCoreApp(int & argc, char ** argv) :
    QApplication(argc, argv)
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
