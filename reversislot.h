#ifndef REVERSISLOT_H
#define REVERSISLOT_H

#include <QObject>
#include <QWidget>
#include  <QPushButton>

class ReversiSlot : public QPushButton
{
    Q_OBJECT
public:
    enum COLOR{BLACK,WHITE};
    ReversiSlot(int x, int y);
    QIcon checker;
    bool DiscIsPlaced();
    void PlaceDisc(ReversiSlot::COLOR);
private: bool is_placed;
};

#endif // REVERSISLOT_H
