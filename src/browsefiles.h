#ifndef BROWSEFILES_H
#define BROWSEFILES_H

#include <QWidget>
#include <QFileDialog>
#include <QVBoxLayout>
/**
 * @brief Utility class to browse for profile picture on system
 */
class BrowseFiles : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief BrowseFiles constructor intializes QFileDialog and widget display of class.
     *
     * Allowed files are images (e.g. jpg, png etc)
     * @param parent
     */
    explicit BrowseFiles(QWidget *parent = nullptr);
    QString directory;
    QWidget * disp;
    QFileDialog * browse;
    QVBoxLayout * layout;
    QString * dir;
public slots:
    /**
     * @brief ChooseFile. Saves the directory of selected image file as a QString in class variable dir
     */
    void ChooseFile();

signals:


};


#endif // BROWSEFILES_H
