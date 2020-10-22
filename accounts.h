#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <QString>
#include <QDir>
#include <QFile>
#include "simplecrypt.h"
#include <QDateTime>
#include <QTextStream>
#include <algorithm>
#include <vector>
#include <QApplication>

class Accounts
{
public:
    Accounts(QString username,QString password, QString confirmPass, QString DOB, QString email, QString fName,QString lName,QString imgPath);
    Accounts(QString username,QString password);
    QString AttemptSignUp();
    QString AttemptSignIn();
    QString UpdateHistory(double score, int game);
    QString GetDOB();
    QString GetImgPath();
    QString GetUsername();
    QString GetFName();

private:bool ValidateEmail(QString email);
     QString EncryptPass(QString plaintext);
     QString DecryptPass(QString ciphertext);
     long key;
     QString username;
     QString password;
     QString confirm_pass;
     QString email;
     QString dob;
     QString f_name;
     QString l_name;
     QString img_path;

};

#endif // ACCOUNTS_H
