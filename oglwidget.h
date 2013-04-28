#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QGLWidget>

class QTimer;

class OGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();


protected:
    void initializeGL();
    void paintGL();

    void mouseMoveEvent(QMouseEvent *event);
    void resizeGL(int width, int height);

private:

    // timer
    QTimer *refreshTimer_;

    // current rotation value
    QPointF rotValue_;

    // temporary variables for mouselook
    QPoint tmpMousePos_;
    QPointF tmpRotValue_;

    // is mouse look enabled?
    bool mouseLook_;

};

#endif // OGLWIDGET_H
