#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QWidget>
#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT
signals:
    void clicked();
public:
    void mousePressEvent(QMouseEvent* event);
    //using QLabel::QLabel;
};

#endif // CLICKEDLABEL_H
