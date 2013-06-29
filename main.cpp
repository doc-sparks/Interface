#include <QtGui/QApplication>
#include "interfacecoreview.h"
#include "interfacecoreapp.h"

int main(int argc, char *argv[])
{
    // create the basic application
    InterfaceCoreApp a(argc, argv);

    // create the window
    InterfaceCoreView w( &a );
    w.show();

    // add some nodes for testing
    a.addNode( new ProcessNode( QVector3D(0, 0, 0) ) );
    a.addNode( new ProcessNode( QVector3D(5, 0, 5) ) );
    a.addNode( new ProcessNode( QVector3D(2, 2, 2) ) );
    a.addNode( new ProcessNode( QVector3D(5, 0, -5) ) );

    return a.exec();
}
