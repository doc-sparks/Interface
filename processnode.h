#ifndef PROCESSNODE_H
#define PROCESSNODE_H

#include <QObject>
#include <QVector3D>
#include <GL/glu.h>

class InterfaceCoreView;

class ProcessNode : public QObject
{
    Q_OBJECT

private:
    // display list for thie node type
    GLint displayList_;

    // parent view
    InterfaceCoreView *parentView_;

    // node type - defined for each in constructor
    QString nodeType_;

    // node 3d position
    QVector3D pos_;

public:
    explicit ProcessNode(QVector3D vec, QObject *parent = 0);

    // create the display list
    void draw();

    // return the display list
    GLuint getDisplayList(InterfaceCoreView *view);

    // return the node type
    QString getNodeType();

    // get/set functions
    QVector3D getPos() { return pos_; }

signals:
    
public slots:
    
};

#endif // PROCESSNODE_H
