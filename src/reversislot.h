#ifndef REVERSISLOT_H
#define REVERSISLOT_H

#include <QObject>
#include <QWidget>
#include  <QPushButton>
#include <QPainter>

/**
 * @brief The ReversiSlot class is a utility class used as the building block of Game2Grid.
 *
 * This class inherits from QPushButton, meaning a ReversiSlot is a clickable button but with additional attributes, which are\n
 *
 */
class ReversiSlot : public QPushButton
{
    Q_OBJECT
public:
    int x;
    int y;
    enum COLOR{BLACK,WHITE};
    /**
     * @brief ReversiSlot Constructor. initializes x and y components of slot. Sets is_placed to false meaning no disc is placed on this slot
     * @param x
     * @param y
     */
    ReversiSlot(int x, int y);
    QIcon checker;
    /**
     * @brief Check is slot is empty or if a disc has been placed in it
     * @return this.is_placed
     */
    bool DiscIsPlaced();
    /**
     * @brief PlaceDisc: Set is_placed to true, assign value to checker icon and set current_color to color
     */
    void PlaceDisc(ReversiSlot::COLOR);
    ReversiSlot::COLOR current_color; //0 for white 1 for black
    bool is_placed;
    /**
     * @brief Flip the color of the disc placed on the slot. If white becomes black and vice versa.
     */
    void Flip();
};

#endif // REVERSISLOT_H
