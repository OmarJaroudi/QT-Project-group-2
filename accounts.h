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
/**
 * @brief The Accounts class for user sign in, sign up, and storing credentials in backend
 *
 */
class Accounts
{
public:
    /**
     * @brief Accounts constructor called when attempting to sign up. All fields are automatically read from their QT placeholders
     * @param username: string
     * @param password: string
     * @param confirmPass: string
     * @param DOB: QDate
     * @param email: string
     * @param fName:string firstname
     * @param lName:string lastname
     * @param imgPath: string path of profile picture
     *
     * Also creates a 16 digit hexadecimal key to be used by SimpleCrypt in encrypting and decrypting the password for added security
     */
    Accounts(QString username,QString password, QString confirmPass, QString DOB, QString email, QString fName,QString lName,QString imgPath);

    /**
     * @brief Accounts constructor invoked when attempting to sign in. Only needs username and password.
     * @param username: string
     * @param password: string
     *
     * Also creates a 16 digit hexadecimal key to be used by SimpleCrypt in encrypting and decrypting the password for added security
     */
    Accounts(QString username,QString password);

    /**
     * @brief AttemptSignUp. Reads all needed credentials verifies if they are sound, stores info in text file, and returns result.
     * @return String result of the transaction.
     *
     * Function will directly terminate without accessing backend text file if:\n
     * Any of credentials is empty or NULL\n
     * Email format is not deemed correct according to ValidateEmail()\n
     * Password doesn't meet requirements (at least 8 characters, containing 1 digit, 1 uppercase and 1 lowercase letters)\n
     * Password and confirm password fields don't match\n
     *
     *
     * If the above checks pass, function will query text file, and report negative result if:\n
     * username or email are already taken by another registered user\n
     *
     * If all these flags are passed, function will store all the entered credentials as a string on one line in text file
     * and report success.\n
     * Note: Before writing to the text file, password is encrypted using SimpleCrypt
     */
    QString AttemptSignUp();

    /**
     * @brief AttemptSignIn.  verify that username and password exist in text file.
     *
     * Text file is accessed as read-only and lines are streamed one by one\n
     * For each line, password is decrypted using SimpleCrypt, and line info is compared to account's native username and password
     * If there is a match, text file is closed and function returns success.
     * If EOF is reached without a match, function reports that sign in failed.
     * @return
     */
    QString AttemptSignIn();


    QString UpdateHistory(int score, int game);

    /**
     * @brief Simple getter for DOB variable
     * @return dob
     */
    QString GetDOB();

    /**
     * @brief Getter for image path variable
     * @return img_path
     */
    QString GetImgPath();
    /**
     * @brief Getter for username variable
     * @return username
     */
    QString GetUsername();
    /**
     * @brief Getter for first name variable
     * @return fName
     */
    QString GetFName();

private:
    /**
     * @brief ValidateEmail: verifies that email is proper format of xx@x.x
     * @param email: string
     * @return boolean result
     */
    bool ValidateEmail(QString email);
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
