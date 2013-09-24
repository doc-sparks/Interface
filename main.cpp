#include <QtGui/QApplication>
#include "interfacecoreview.h"
#include "interfacecoreapp.h"
#include "constantnode.h"
#include "mergernode.h"
#include "splitternode.h"
#include "additionnode.h"
#include "stdoutnode.h"
#include "inputdataport.h"
#include "outputdataport.h"

int main(int argc, char *argv[])
{
    // create the basic application
    InterfaceCoreApp a(argc, argv);

    // create the window
    InterfaceCoreView w( &a );
    w.show();

    ////////////////////////////////////////////////
    // set up a loop
    ConstantNode *c1 = new ConstantNode( QVector3D(-5, 0, 0), "ConstNode1" );
    a.addNode( c1 );
    c1->setConstValue( DataValue(1) );

    MergerNode *m = new MergerNode( QVector3D(-3, 0, 0), "MergerNode" );
    a.addNode( m );
    m->setOutputMode(MergerNode::Priority);  // set the merger on port priority, not last push
    m->setNumInputs(2);

    DataPort::connect(c1->getOutput(0), m->getInput(1));

    ConstantNode *c2 = new ConstantNode( QVector3D(-3, -2, 0), "ConstNode2" );
    a.addNode( c2 );
    c2->setConstValue( DataValue(5) );

    AdditionNode *d = new AdditionNode( QVector3D(0, 0, 0), "AdditionNode" );
    a.addNode( d );
    DataPort::connect(m->getOutput(0), d->getInput(0));
    DataPort::connect(c2->getOutput(0), d->getInput(1));

    SplitterNode *s = new SplitterNode( QVector3D(3, 2, 0), "SplitterNode" );
    a.addNode( s );
    s->setNumOutputs(2);
    DataPort::connect(d->getOutput(0), s->getInput(0));
    DataPort::connect(s->getOutput(0), m->getInput(0));

    StdOutNode *o = new StdOutNode( QVector3D(5, 0, 0), "StdOutNode" );
    a.addNode( o );
    DataPort::connect(s->getOutput(1), o->getInput(0));

    // init
    a.initialiseNodes();

    return a.exec();
}
