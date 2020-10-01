#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <accounts.h>
#include <QtWidgets>
#include <QTimer>
#include <QObject>

class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuWidget(QWidget *parent = nullptr);
    Accounts * currentUser;
    QLabel *log;
    QGridLayout * grid;
    QVBoxLayout * VBox;
    QLabel *birthday;
    QLabel *currentDateLabel;
    QLabel *img;
    QTimer *timer;
    void prepareMenu(Accounts * curr);
private slots:void blink();
signals:

};

#endif // MAINMENU_H
