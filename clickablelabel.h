#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QWidget>
#include <QLabel>
/**
 * @brief The ClickableLabel class. inherits from QLabel but with signal clicked to be emitted on mousePressEvent
 *
 */
class ClickableLabel : public QLabel
{
    Q_OBJECT
signals:
    /**
     * @brief signal emitted when label is clicked on with mouse
     */
    void clicked();
public:
    void mousePressEvent(QMouseEvent* event);
    /**
     * @brief ClickableLabel default constructor
     */
    ClickableLabel();
};

#endif // CLICKEDLABEL_H
