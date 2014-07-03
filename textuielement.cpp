#include "textuielement.h"

TextUIElement::TextUIElement()
{
}

void TextUIElement::paint(QPainter *painter)
{
    // write the text
    painter->drawText(rect_, text_);
}
