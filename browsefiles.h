#ifndef BROWSEFILES_H
#define BROWSEFILES_H

#include <QWidget>
#include <QtWidgets>

class BrowseFiles : public QWidget
{
    Q_OBJECT
public:
    explicit BrowseFiles(QWidget *parent = nullptr);
    QString directory;
    QWidget * Disp;
    QFileDialog * Browse;
    QVBoxLayout * layout;
    QString * Dir;
public slots:
    void ChooseFile();

signals:


};


#endif // BROWSEFILES_H
