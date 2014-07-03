#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <QObject>
#include <QPainter>

class UIElement : public QObject
{
    Q_OBJECT
public:
    explicit UIElement(QObject *parent = 0);
    
    // paint this UI Element
    virtual void paint(QPainter *painter);

    // set the rectangle
    void setRect( QRect r ) { rect_ = r; }

protected:
    QRect rect_;

signals:
    
public slots:
    
};

#endif // UIELEMENT_H
