#ifndef SIGNINWIDGET_H
#define SIGNINWIDGET_H

#include <QWidget>
#include<QtWidgets>
#include <QString>
#include "accounts.h"

class SignInWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SignInWidget(QWidget *parent = nullptr);
    QLabel * username;
    QLabel * password;
    QLineEdit * usernameBox;
    QLineEdit * passBox;
    QPushButton * LogIn;
    QHBoxLayout *hbox;
    QGridLayout * grid;
    QVBoxLayout * layout;
    QLabel * errorMessage;
    QPushButton * Back;

public slots:
    void verifyCredentials();
    void ClickReturn();
signals:

};

#endif // SIGNINCLASS_H
