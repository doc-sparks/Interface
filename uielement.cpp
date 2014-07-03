#include "uielement.h"

UIElement::UIElement(QObject *parent) :    
    QObject(parent),
    rect_(0, 0, 200, 100)
{
}

void UIElement::paint(QPainter *painter)
{

}
