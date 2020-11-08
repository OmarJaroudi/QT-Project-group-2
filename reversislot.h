#ifndef REVERSISLOT_H
#define REVERSISLOT_H

#include <QObject>
#include <QWidget>
#include  <QPushButton>

class ReversiSlot : public QPushButton
{
    Q_OBJECT
public:
    ReversiSlot(int x, int y);
    QIcon white_checker;
};

#endif // REVERSISLOT_H
