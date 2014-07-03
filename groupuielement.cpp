#include "groupuielement.h"

GroupUIElement::GroupUIElement() : border_(8)
{

}

void GroupUIElement::paint(QPainter *painter)
{
    // paint the group area
    QColor c = QColor(26, 63, 82, 128);

    // widget area
    painter->fillRect( rect_, c );

    // outline
    QPen p(QColor(172, 194, 191, 128), 3);
    painter->setPen( p );
    painter->drawLine(rect_.left() + 1, rect_.top() + 1 + rect_.height() - 5, rect_.left() + 1, rect_.top() + rect_.height());
    painter->drawLine(rect_.left() + 1 + 5, rect_.top() + 1 + rect_.height(), rect_.left() + 1, rect_.top() + rect_.height());
    painter->drawLine(rect_.left() + rect_.width() - 5, rect_.top() + 1, rect_.left() + rect_.width(), rect_.top() + 1);
    painter->drawLine(rect_.left() + rect_.width(), rect_.top() + 1, rect_.left() + rect_.width(), rect_.top() + 1 + 5);

    // paint all containing UIElements
    for (int i = 0; i < uiElements_.count(); i++)
    {        
        uiElements_.at(i)->paint(painter);
    }
}

void GroupUIElement::addElement(UIElement *e)
{
    // add the element
    uiElements_.append(e);

    // rearrange all the elemnts to accomodate
    for (int i = 0; i < uiElements_.count(); i++)
    {
        uiElements_.at(i)->setRect( QRect(rect_.x() + border_,
                                          rect_.y() + border_ + i * (rect_.height() / uiElements_.count() ),
                                          rect_.width() - 2 * border_,
                                          rect_.height() / uiElements_.count() - 2 * border_ ) );
    }
}
