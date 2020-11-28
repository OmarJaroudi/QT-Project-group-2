#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once

#include <QWidget>
#include "accounts.h"
#include "game1.h"
#include "game2.h"
#include <QTimer>
#include <QObject>
#include <QDateEdit>
#include "clickablelabel.h"
#include "historywidget.h"

class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief MainMenuWidget constructor: Sets text and icons for different labels.
     *
     * Gets account's username from current_user, and gets their dob.\n
     * If its the user's birthday, a happy birthday blinking message is displayed
     * @param curr: Account that is currently signed in (Can be guest account)
     * @param parent
     */
    explicit MainMenuWidget(Accounts *curr, QWidget *parent = nullptr);
    Accounts * current_user;
    QLabel *log;
    QLabel *welcome;
    QGridLayout * grid;
    QVBoxLayout * vbox;
    QGridLayout * game_grid;
    QLabel *birthday;
    QLabel *img;
    QTimer *timer;
    QSpacerItem *bigSpacer;
    QPushButton *logout;
    QPushButton *history;
    ClickableLabel *game_1_label;
    ClickableLabel *game_2_label;

private slots:
    /**
     * @brief Blink: Slot connected to a flashing timer that displays and hides the happy birthday message in case user logs in on their borthday
     */
    void Blink();
    /**
     * @brief PlayGame1: Slot connected to clicked() signal of game_1_label. Instantiates object of type Game1 and closes the current instance of MainMenuWidget
     */
    void PlayGame1();
    /**
     * @brief PlayGame1: Slot connected to clicked() signal of game_2_label. Instantiates object of type Game2 and closes the current instance of MainMenuWidget
     */
    void PlayGame2();
    /**
     * @brief LogOut: Slot connected to clicked() signal of logout pushbutton. Closes instance of MainMenuWidget and instantiates new object of type WelcomeWidget
     */
    void LogOut();
    /**
     * @brief history_clicked: Slot connected to clicked() signal of history pushbutton. Instantiates object of type historywidget
     */
    void HistoryClicked();
signals:

};

#endif // MAINMENU_H
