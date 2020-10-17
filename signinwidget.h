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
    QLineEdit * username_box;
    QLineEdit * pass_box;
    QPushButton * log_in;
    QHBoxLayout *hbox;
    QGridLayout * grid;
    QVBoxLayout * layout;
    QLabel * error_message;
    QPushButton * back_button;

public slots:
    void VerifyCredentials();
    void ClickReturn();
signals:

};

#endif // SIGNINCLASS_H
