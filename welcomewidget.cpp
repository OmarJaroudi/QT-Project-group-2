#include "welcomewidget.h"
#include "signinwidget.h"
#include "signupwidget.h"
#include "accounts.h"
#include "mainmenuwidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);

    //setting background color
    QColor col = QColor::fromRgb(148,0,211);
    QColor backgroundColor = QColor::fromRgb(33,33,35);
    this->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));

    //setting up the widgets
    welcome = new QLabel("Welcome!");
    welcome->setAlignment(Qt::AlignCenter);
    QFont f = welcome->font();
    f.setPointSize(20);
    welcome->setFont(f);
    welcome->setStyleSheet(QString("color: %1").arg(col.name()));

    f.setPointSize(15);

    sign_in = new QPushButton("Sign in");
    sign_in->setFont(f);
    sign_in->setStyleSheet(QString("background-color: %1").arg(col.name()));


    sign_up = new QPushButton("Sign up");
    sign_up->setFont(f);
    sign_up->setStyleSheet(QString("background-color: %1").arg(col.name()));

    play_as_guest = new QPushButton("Continue as guest");
    play_as_guest->setFont(f);
    play_as_guest->setStyleSheet(QString("background-color: %1").arg(col.name()));

    //adding the widgets to a vbox layout
    vbox = new QVBoxLayout();
    vbox->addWidget(welcome);
    vbox->addWidget(sign_in);
    vbox->addWidget(sign_up);
    vbox->addWidget(play_as_guest);
    this->setLayout(vbox);

    //signal slot connections
    QObject::connect(sign_in,SIGNAL(clicked()),this,SLOT(SignInButton()));
    QObject::connect(sign_up,SIGNAL(clicked()),this,SLOT(SignUpButton()));
    QObject::connect(play_as_guest,SIGNAL(clicked()),this,SLOT(PlayAsGuestButton()));


}
void WelcomeWidget::SignInButton(){//transitions to signInWidget
    SignInWidget * signInWidget = new SignInWidget();
    signInWidget->show();
    this->close();

}
void WelcomeWidget::SignUpButton(){//transitions to sign_upWidget
    SignUpWidget * sign_upWidget = new SignUpWidget();
    sign_upWidget->show();
    this->close();
}
void WelcomeWidget::PlayAsGuestButton(){//transitions to MainMenuWidget with Account set as a guest
    Accounts * guestAcc = new Accounts("Guest player","","","","","","",":/thumbnails/blank_profile.png");
    MainMenuWidget * menu = new MainMenuWidget(guestAcc);
    this->close();
}

