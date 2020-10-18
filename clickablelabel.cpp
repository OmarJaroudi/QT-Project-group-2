#include "clickablelabel.h"

void ClickableLabel::mousePressEvent(QMouseEvent* event1)
{
    emit clicked();
}

ClickableLabel::ClickableLabel(QString color){
    this->color = color;
}
ClickableLabel::ClickableLabel(){}
