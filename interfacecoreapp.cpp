#include "interfacecoreapp.h"
#include <QVector3D>

InterfaceCoreApp::InterfaceCoreApp(int & argc, char ** argv) :
    QApplication(argc, argv)
{
    // add some nodes for testing
    addNode( new ProcessNode( QVector3D(0, 0, 0) ) );
    addNode( new ProcessNode( QVector3D(5, 0, 5) ) );
}

void InterfaceCoreApp::addNode( ProcessNode *node )
{
    // add the given node to the list
    processNodes_.append( node );
}
