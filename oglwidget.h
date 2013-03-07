#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QGLWidget>

class QtLogo;

class OGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();


protected:
    void initializeGL();
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeGL(int width, int height);

private:
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
    GLfloat     rtri;

};

#endif // OGLWIDGET_H
