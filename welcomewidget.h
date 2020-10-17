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
    QLabel * welcome;
    QPushButton * sign_in;
    QPushButton * sign_up;
    QPushButton * play_as_guest;
    QVBoxLayout * vbox;

public slots:
    void SignInButton();
    void SignUpButton();
    void PlayAsGuestButton();
signals:

};

#endif // WELCOMEWIDGET_H
