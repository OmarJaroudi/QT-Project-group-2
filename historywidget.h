#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H
#include <QApplication>
#include <QWidget>
#include<QObject>
#include <QtWidgets>
#include <accounts.h>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <mainmenuwidget.h>

/**
 * @brief The Game1 class instantiated when user clicks on game1 from main menu
 */
class historyWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief historyWidget constructor, needs to know the account of the user that is logged in to show the user's scores
     * @param curr
     * @param parent
     */
    explicit historyWidget(Accounts * curr,QWidget *parent = nullptr);
    bool b=true;//when true game1 is shown, when false game2 is shown
    QPushButton * switchGames;
    QHBoxLayout * topButtonBox;
    QLabel * highscoreLabel1;
    QLabel * highscoreLabel2;
    QLabel * username_header;
    QLabel * score_header;
    QLabel * date_header;
    QLabel * rank_header;
    QLabel * username_header2;
    QLabel * score_header2;
    QLabel * date_header2;
    QLabel * rank_header2;
    QLabel * username_top1;
    QLabel * score_top1;
    QLabel * date_top1;
    QLabel * username_top2;
    QLabel * score_top2;
    QLabel * date_top2;
    QLabel * username_top3;
    QLabel * score_top3;
    QLabel * date_top3;
    QLabel * username_top4;
    QLabel * score_top4;
    QLabel * date_top4;
    QLabel * username_top5;
    QLabel * score_top5;
    QLabel * date_top5;

    QLabel * highscoreLabel12;
    QLabel * highscoreLabel22;
    QLabel * username_top12;
    QLabel * score_top12;
    QLabel * date_top12;
    QLabel * username_top22;
    QLabel * score_top22;
    QLabel * date_top22;
    QLabel * username_top32;
    QLabel * score_top32;
    QLabel * date_top32;
    QLabel * username_top42;
    QLabel * score_top42;
    QLabel * date_top42;
    QLabel * username_top52;
    QLabel * score_top52;
    QLabel * date_top52;

    QLabel * rank1;
    QLabel * rank2;
    QLabel * rank3;
    QLabel * rank4;
    QLabel * rank5;

    QLabel * rank12;
    QLabel * rank22;
    QLabel * rank32;
    QLabel * rank42;
    QLabel * rank52;

    QVBoxLayout * Vbox1;
    QGridLayout * Grid1;
    QVBoxLayout * Vbox2;
    QGridLayout * Grid2;
    QStackedLayout *View;

    QVBoxLayout * mainLayout;

    QWidget * historyTopPage1;
    QWidget * historyTopPage2;

private slots:
    void changeGame();
    /**
     * @brief changeGame: slot executes when switchGames is pushed
     *
     * Switches the widgets to show game1 or game2 scores.
     */

signals:

};

#endif // HISTORYWIDGET_H
