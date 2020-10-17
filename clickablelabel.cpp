#include "clickablelabel.h"

void ClickableLabel::mousePressEvent(QMouseEvent* event1)
{
    emit clicked();
}
