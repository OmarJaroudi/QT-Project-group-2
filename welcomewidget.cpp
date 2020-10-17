#include "welcomewidget.h"
#include "signinwidget.h"
#include "signupwidget.h"
#include "accounts.h"
#include "mainmenuwidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent)
{
    QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
    this->move(-500000,-500000);
    this->move((primaryScreenGeometry.width() - this->width()) / 2.0,
                    (primaryScreenGeometry.height() - this->height()) / 2.0);

    //setting background color
    QColor col = QColor::fromRgb(148,0,211);
    QColor backgroundColor = QColor::fromRgb(33,33,35);
    this->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));

    //setting up the widgets
    Welcome = new QLabel("Welcome!");
    Welcome->setAlignment(Qt::AlignCenter);
    QFont f = Welcome->font();
    f.setPointSize(20);
    Welcome->setFont(f);
    Welcome->setStyleSheet(QString("color: %1").arg(col.name()));

    f.setPointSize(15);

    SignIn = new QPushButton("Sign in");
    SignIn->setFont(f);
    SignIn->setStyleSheet(QString("background-color: %1").arg(col.name()));


    SignUp = new QPushButton("Sign up");
    SignUp->setFont(f);
    SignUp->setStyleSheet(QString("background-color: %1").arg(col.name()));

    PlayAsGuest = new QPushButton("Continue as guest");
    PlayAsGuest->setFont(f);
    PlayAsGuest->setStyleSheet(QString("background-color: %1").arg(col.name()));

    //adding the widgets to a Vbox layout
    VBox = new QVBoxLayout();
    VBox->addWidget(Welcome);
    VBox->addWidget(SignIn);
    VBox->addWidget(SignUp);
    VBox->addWidget(PlayAsGuest);
    this->setLayout(VBox);

    //signal slot connections
    QObject::connect(SignIn,SIGNAL(clicked()),this,SLOT(SignInButton()));
    QObject::connect(SignUp,SIGNAL(clicked()),this,SLOT(SignUpButton()));
    QObject::connect(PlayAsGuest,SIGNAL(clicked()),this,SLOT(PlayAsGuestButton()));


}
void WelcomeWidget::SignInButton(){//transitions to signInWidget
    SignInWidget * signInWidget = new SignInWidget();
    signInWidget->show();
    this->close();

}
void WelcomeWidget::SignUpButton(){//transitions to signUpWidget
    SignUpWidget * signUpWidget = new SignUpWidget();
    signUpWidget->show();
    this->close();
}
void WelcomeWidget::PlayAsGuestButton(){//transitions to MainMenuWidget with Account set as a guest
    Accounts * guestAcc = new Accounts("Guest player","","","","","","",":/thumbnails/blank_profile.png");
    MainMenuWidget * menu = new MainMenuWidget();
    this->hide();
    menu->prepareMenu(guestAcc);
}

