#ifndef PROCESSNODE_H
#define PROCESSNODE_H

#include <QObject>
#include <QVector3D>

class ProcessNode : public QObject
{
    Q_OBJECT

private:


public:
    explicit ProcessNode(QVector3D vec, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // PROCESSNODE_H
