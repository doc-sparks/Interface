#ifndef TEXTUIELEMENT_H
#define TEXTUIELEMENT_H

#include "uielement.h"

class TextUIElement : public UIElement
{
public:
    TextUIElement();

    // paint this UI Element
    virtual void paint(QPainter *painter);

    // set the text
    void setText( QString t ) { text_ = t; }

private:
    QString text_;

};

#endif // TEXTUIELEMENT_H
