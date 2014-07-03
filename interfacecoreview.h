#ifndef INTERFACECOREVIEW_H
#define INTERFACECOREVIEW_H

#include <QMainWindow>
#include <QMap>
#include "interfacecoreapp.h"
#include <GL/glu.h>
#include "uielement.h"
#include "oglwidget.h"

namespace Ui {
class InterfaceCoreView;
}

class InterfaceCoreView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit InterfaceCoreView(InterfaceCoreApp *app, QWidget *parent = 0);
    ~InterfaceCoreView();
    
    // check key status
    bool isKeyDown(int key);

    // node drawing routines
    void createDisplayLists();
    void drawNodes();
    void drawConnections();
    GLuint getDisplayList( QString node );
    void setHighightedObject(int i) { highlightedObject_ = i; }

    // UI drawing
    void drawNodeUIElements(QPainter *p);
    void drawFixedUIElements(QPainter *p);

private:

    // keyboard map for deciding key presses
    QMap<int, bool> keyboardMap_;

    // application pointer
    InterfaceCoreApp *app_;

    // map between node type and display list
    QMap<QString, GLuint> displayListMap_;

    // hard coded UI Elements for interface controls, etc.
    QList<UIElement*> fixedUIElements_;

    // which object has the mouse under it
    int highlightedObject_;

    // selected object
    int selectedObject_;

    // the widget that stores position, etc.
    OGLWidget *oglWidget_;

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // INTERFACECOREVIEW_H
