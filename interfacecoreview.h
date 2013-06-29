#ifndef INTERFACECOREVIEW_H
#define INTERFACECOREVIEW_H

#include <QMainWindow>
#include <QMap>
#include "interfacecoreapp.h"
#include <GL/glu.h>

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
    GLuint getDisplayList( QString node );

private:

    // keyboard map for deciding key presses
    QMap<int, bool> keyboardMap_;

    // application pointer
    InterfaceCoreApp *app_;

    // map between node type and display list
    QMap<QString, GLuint> displayListMap_;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // INTERFACECOREVIEW_H
