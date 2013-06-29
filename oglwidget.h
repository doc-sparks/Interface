#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QGLWidget>

class QTimer;
class InterfaceCoreView;

class OGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    OGLWidget(InterfaceCoreView *view, QWidget *parent = 0);
    ~OGLWidget();

protected:
    void initializeGL();
    void paintGL();

    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);    
    void resizeGL(int width, int height);    

private:

    // parent window
    InterfaceCoreView *parentView_;

    // timer
    QTimer *refreshTimer_;

    // current rotation value
    QPointF rotValue_;

    // current camera centred position
    QPointF posValue_;

    // current camera zoom value
    double zoomValue_;

    // temporary variables for mouselook
    QPoint tmpMousePos_;
    QPointF tmpRotValue_;

    // is mouse look enabled?
    bool mouseLook_;    

protected slots:
    void mainLoop();
};

#endif // OGLWIDGET_H
