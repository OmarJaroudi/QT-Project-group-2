#include "accounts.h"
#include <QDebug>

Accounts::Accounts(QString username,QString password, QString confirmPass, QString DOB, QString email, QString fName,QString lName,QString imgPath)
{
    key = Q_UINT64_C(0x0c2ad4a4acb9f023);//encryption key
    this->username = username;
    this->password = password;
    this->confirm_pass = confirmPass;
    this ->email = email;
    this->dob = DOB;
    this->f_name = fName;
    this->l_name = lName;
    this->img_path = imgPath;

}
Accounts::Accounts(QString username,QString password)//basic constructor passed for a sign in
{
    key = Q_UINT64_C(0x0c2ad4a4acb9f023);
    this->username = username;
    this->password = password;

}
QString Accounts::AttemptSignIn(){//
    if (username==NULL || password == NULL){
        return("username or password field is empty!");
    }
    else {
        bool found = false;
        bool verified = false;
        QString found_username = "";
        //access the txt file where the info is stored
        QString path = QDir::currentPath();
        path.append("/userData/data.txt");
        QFile inputFile(path);
        if (inputFile.size()!=0){
        inputFile.open(QIODevice::ReadOnly);//configure to read and write
        QTextStream stream(&inputFile);
            QString line = stream.readLine();
            while (!line.isNull()) { //extract info from txt file to verify
                QStringList tempLine = line.split(" ");
                if (tempLine[0]==username || tempLine[2]==username){//check username or email exist
                    found = true;
                    if (DecryptPass(tempLine[1])==password){//check password match
                        //set the rest of the Account parameters
                        found_username = tempLine[0];
                        verified = true;
                        this->username = tempLine[0];
                        this->email = tempLine[2];
                        this->f_name = tempLine[3];
                        this->l_name = tempLine[4];
                        this->dob = tempLine[5];
                        this->img_path = tempLine[6];
                        break;
                    }
                }
                line = stream.readLine();
            }
        }

        //return success or an error message
        if (verified==true && found==true)
            return("success");
        else if (found == true)
            return("Password is incorrect!");
        else
            return("Username or email doesn't exist!");
    }
}

QString Accounts::AttemptSignUp(){
QRegExp re("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])");
    if(username==NULL||
            password==NULL||
            confirm_pass == NULL ||
            f_name == NULL ||
            l_name == NULL ||
            email == NULL||
            dob == NULL) {
        return("Error empty field(s)!");//checks for empty fields
    }

    if(username.contains(" ")||
            password.contains(" ")||
            confirm_pass.contains(" ") ||
            f_name.contains(" ") ||
            l_name.contains(" ") ||
            email.contains(" ")) {
        return("Fields cannot contain whitespace!");//checks for the presence of any whitespace. Whitespaces are used to sperate info in the txt file.
    }

    else if (!ValidateEmail(email)){//validate possible email
        return("Invalid email address!");
    }
    else if (password!=confirm_pass){//pass!=confirm pass
        return("Passwords don't match!");
    }
    else if(password.length()<8){//password too short
        return("Password must be longer than 8 characters!");
    }
    else if (re.indexIn(password)==-1){//password does not meet other requirements
        return("Password must contain 1 uppercase char, \n1 lowecase char, and 1 number!");
    }
    else {
        //set up to write to the txt file
        QString path = QDir::currentPath();
        path.append("/userData");
        if (!QDir(path).exists())
            QDir().mkdir(path);
        path.append("/data.txt");

        QFile inputFile(path);
        inputFile.open(QIODevice::ReadWrite);
        QTextStream stream(&inputFile);
        if (inputFile.size()!=0){
            QString line = stream.readLine();
            while (!line.isNull()) {
                QStringList tempLine = line.split(" ");
                if (tempLine[0]==username)//check for duplicate username
                    return("Username already taken!");
                else if (tempLine[2]==email)//check for duplicate email
                    return("Email already registered!");
                line = stream.readLine();
            }
        }
        if (img_path==NULL)//no picture selected
            return ("Please select a profile picture!");

        //add image directory into the info string
        QFileInfo imgInfo(img_path);
        QString newPath = QDir::currentPath();
        newPath.append("/userDP");
        if (!QDir(newPath).exists())
            QDir().mkdir(newPath);
        newPath.append("/" + username+ "." + imgInfo.suffix());
        qDebug()<<newPath;
        if (QFile::exists(newPath))
        {
            QFile::remove(newPath);
        }

        //write all the account info into the txt file
        bool status = QFile::copy(img_path, newPath);
        if (status == false)
            return ("Error adding profile picture!");
        QString data = (username + " " +
                    EncryptPass(password) + " " +
                    email + " " +
                    f_name + " " +
                    l_name + " " +
                    dob + " " +
                    newPath);
        this->img_path = newPath;
        stream<<data<<endl;
        inputFile.close();
        QString path2 = qApp->applicationDirPath();
        path2.append("/userData/game_1_history.txt");
        QFile inputFile2(path2);
        inputFile2.open(QIODevice::ReadWrite);
        QTextStream stream2(&inputFile2);
        if (inputFile2.size()!=0){
            QString line = stream2.readLine();
            while (line.isNull()) {
                line=stream2.readLine();
            }
        }
        QDateTime curr_date_time = QDateTime::currentDateTime();
        data=(username+" 0 "+ curr_date_time.toString());
        stream2<<data<<endl;
        inputFile2.close();
        QString path3 = qApp->applicationDirPath();
        path3.append("/userData/game_2_history.txt");
        QFile inputFile3(path3);
        inputFile3.open(QIODevice::ReadWrite);
        QTextStream stream3(&inputFile3);
        if (inputFile3.size()!=0){
            QString line1 = stream3.readLine();
            while (line1.isNull()) {
                line1=stream3.readLine();
            }
        }
        data=(username+" 0 "+ curr_date_time.toString());
        stream3<<data<<endl;
        inputFile3.close();
        return "success";
    }

}

QString Accounts::UpdateHistory(int score, int game)
{
    QDateTime curr_date_time = QDateTime::currentDateTime();
    if(game==1 || game==2)
    {
        QString scoreString= QString::number(score);
        QString gameString= QString::number(game);
        std::vector<QString> tempData;
        std::vector<int> tempScores;
        QString path = qApp->applicationDirPath();
        path.append("/userData/game_"+gameString+"_history.txt");
        QString data;
        QFile inputFile(path);
        inputFile.open(QIODevice::ReadWrite);
        QTextStream stream(&inputFile);
        if (inputFile.size()!=0){
            QString line = stream.readLine();
            while (line!="") {
                QStringList tempLine = line.split(" ");
                if(this->username==tempLine[0])
                {
                    if(tempLine[game].toDouble()<score)
                    {
                        data=tempLine[0]+" "+scoreString+" "+curr_date_time.toString();
                        tempData.push_back(data);
                        tempScores.push_back(score);
                    }
                    else return "up to date";
                }
                else
                {
                    tempData.push_back(line);
                    tempScores.push_back(tempLine[1].toInt());
                    qDebug()<<tempLine[2];
                }
                line= stream.readLine();
            }

            std::sort(tempScores.begin(),tempScores.end());
            std::reverse(tempScores.begin(),tempScores.end());
            std::vector<QString> sortedData;
            sortedData.assign(tempScores.size(),"");

            for(int i=0;i<tempScores.size();i++)
            {
                QStringList tempLine1 = tempData[i].split(" ");
                for(int j=0;j<tempScores.size();j++)
                {
                    if(tempLine1[1].toInt()==tempScores[j])
                    {
                        sortedData[j]=tempData[i];
                        tempScores[j]=-1;
                        break;
                    }
                }
            }
            inputFile.resize(0);
            QTextStream stream2(&inputFile);
            QString finalAdd="";
            for(int i=0; i<sortedData.size();i++)
            {
                finalAdd.append(sortedData[i]+"\n");
            }
            stream2.seek(0);
            stream2<<finalAdd;
            inputFile.close();
            return "succesfully updated";
        }
    }
    else return "not a valid game number";
}
bool Accounts::ValidateEmail(QString email){//check if the string entered is really an email (doesnt have to be active)
    email = email.toLower();
    QRegExp re("([a-z]+)([_.a-z0-9]*)([a-z0-9]+)(@)([a-z]+)([.a-z]+)([a-z]+)");
    if (re.exactMatch(email))
        return true;

    return false;
}
//encyrpt and decrypt
QString Accounts::EncryptPass(QString plaintext){
   SimpleCrypt crypto(this->key);
    return (crypto.encryptToString(plaintext));
}

QString Accounts::DecryptPass(QString ciphertext){
    SimpleCrypt crypto(this->key);
    return(crypto.decryptToString(ciphertext));
}

//setters and getters
QString  Accounts::GetDOB(){
    return dob;
}

QString  Accounts::GetUsername(){
    return username;
}
QString  Accounts::GetFName(){
    return f_name;
}
QString  Accounts::GetImgPath(){
    return img_path;
}

