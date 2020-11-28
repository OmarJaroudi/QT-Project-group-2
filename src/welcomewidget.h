#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H
#include <QWidget>
#include<QObject>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief WelcomeWidget constructor
     * @param parent
     */
    explicit WelcomeWidget(QWidget *parent = nullptr);
    QLabel * welcome;
    QPushButton * sign_in;
    QPushButton * sign_up;
    QPushButton * play_as_guest;
    QVBoxLayout * vbox;

public slots:
    /**
     * @brief SignInButton: slot executes when the sign in button is pushed
     *
     * switches to the SignInWidget and deletes the current widget
     */
    void SignInButton();
    /**
     * @brief SignUpButton: slot executes when the sign up button is pushed
     *
     * switches to the SignUpWidget and deletes the current widget
     */
    void SignUpButton();
    /**
     * @brief PlayAsGuestButton: slot executes when the play as guest button is pushed
     *
     * switches to the mainmenuwidget with the account set as guest and deletes the current widget
     */
    void PlayAsGuestButton();
signals:

};

#endif // WELCOMEWIDGET_H
