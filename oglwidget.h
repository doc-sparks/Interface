#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QGLWidget>
#include <QVector3D>

class QTimer;
class InterfaceCoreView;

class OGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    OGLWidget(InterfaceCoreView *view, QWidget *parent = 0);
    ~OGLWidget();

    // external setting of pos and rot
    void setPosition(QVector3D pos) { posValue_ = pos; }

protected:
    void initializeGL();
    //void paintGL();  // use paintEvent instead
    void paintEvent(QPaintEvent *);
    void paint3D();
    void paint2D();

    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);    
    void resizeGL(int width, int height);    

    int getObjectAtScreenPos(int x, int y);


private:

    // parent window
    InterfaceCoreView *parentView_;

    // timer
    QTimer *refreshTimer_;

    // current rotation value
    QPointF rotValue_;

    // current camera centred position
    QVector3D posValue_;

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
