#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "browsefiles.h"
#include "accounts.h"

class SignUpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SignUpWidget(QWidget *parent = nullptr);
    BrowseFiles * Browser;
    QLabel * imgLocation;
    QLabel * errorMessage;
    QLabel * Prompt;
    QLabel * FirstName;
    QLabel * LastName;
    QLabel * Username;
    QLabel * Email;
    QLabel * Password;
    QLabel * ConfirmPassword;
    QLabel * BirthDate;
    QLabel * ProfilePic;
    QPushButton * Create;
    QPushButton * Back;
    QLineEdit * FirstNameBox;
    QLineEdit * LastNameBox;
    QLineEdit * UsernameBox;
    QLineEdit * EmailBox;
    QLineEdit * PasswordBox;
    QLineEdit * ConfirmPasswordBox;
    QGridLayout * Grid;
    QDateEdit * Date;
    QFileDialog * Browse;
    QPushButton * ChoosePic;

public slots:
    void BrowseForImage();
    void ClickReturn();
    void CreateAccount();


signals:

};

#endif // SIGNUPCLASS_H
