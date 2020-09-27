#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include<QObject>
#include <QtWidgets>
class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    QLabel * Welcome;
    QPushButton * SignIn;
    QPushButton * SignUp;
    QPushButton * PlayAsGuest;
    QVBoxLayout * VBox;

public slots:
    void SignInButton();
    void SignUpButton();
    void PlayAsGuestButton();
signals:

};

#endif // WELCOMEWIDGET_H
