#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <accounts.h>
#include <game1.h>
#include <QtWidgets>
#include <QTimer>
#include <QObject>

class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuWidget(Accounts *curr, QWidget *parent = nullptr);
    QPushButton * game_1_button;
    Accounts * current_user;
    QLabel *log;
    QGridLayout * grid;
    QVBoxLayout * vbox;
    QLabel *birthday;
    QLabel *current_date_label;
    QLabel *img;
    QTimer *timer;
private slots:
    void Blink();
    void PlayGame1();
signals:

};

#endif // MAINMENU_H
