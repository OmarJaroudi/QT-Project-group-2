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
    BrowseFiles * browser;
    QLabel * img_location;
    QLabel * error_message;
    QLabel * prompt;
    QLabel * first_name;
    QLabel * last_name;
    QLabel * username;
    QLabel * email;
    QLabel * password;
    QLabel * confirm_password;
    QLabel * birth_date;
    QLabel * profile_pic;
    QPushButton * create;
    QPushButton * back_button;
    QLineEdit * first_name_box;
    QLineEdit * last_name_box;
    QLineEdit * username_box;
    QLineEdit * email_box;
    QLineEdit * password_box;
    QLineEdit * confirm_password_box;
    QGridLayout * grid;
    QDateEdit * date;
    QFileDialog * browse;
    QPushButton * choose_pic;

public slots:
    void BrowseForImage();
    void ClickReturn();
    void CreateAccount();


signals:

};

#endif // SIGNUPCLASS_H
