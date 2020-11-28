#ifndef SIGNINWIDGET_H
#define SIGNINWIDGET_H
#pragma once

#include <QWidget>
#include <QString>
#include "accounts.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>


/**
 * @brief The SignInWidget class instantiated when user clicks sign in from welcome screen
 */
class SignInWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief SignInWidget constructor
     * @param parent
     */
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
    Accounts *account;

public slots:
    /**
     * @brief VerifyCredentials: slot executes when the sign in button is pushed
     *
     * passes the input to attemptSignIn
     */
    void VerifyCredentials();
    /**
     * @brief VerifyCredentials: slot executes when the return button is pushed
     *
     * returns the user to the welcome screen.
     */
    void ClickReturn();
signals:

};

#endif // SIGNINCLASS_H
