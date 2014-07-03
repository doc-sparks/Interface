#ifndef GROUPUIELEMENT_H
#define GROUPUIELEMENT_H

#include "uielement.h"

class GroupUIElement : public UIElement
{
public:
    GroupUIElement();

    // paint this UI Element
    virtual void paint(QPainter *painter);

    // add element
    void addElement(UIElement *e);

    // get an element
    UIElement *getElement(int i) { return uiElements_.at(i); }

private:

    // list of contained UIElements
    QList<UIElement*> uiElements_;

    // border
    int border_;
};

#endif // GROUPUIELEMENT_H
