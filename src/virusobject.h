#ifndef VIRUSOBJECT_H
#define VIRUSOBJECT_H
#include "clickablelabel.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
using namespace std;
class VirusObject : public ClickableLabel
{
    Q_OBJECT
public:
    enum Color {GREEN,YELLOW,BLUE};
    QString getColor();
    int getScore();
    int getSize();
    VirusObject();
    QMediaPlayer *smash_sound;
    QTimer * expiry_timer;
    /**
     * @brief VirusObject constructor
     * @param parent
     */
    VirusObject(VirusObject::Color c,double speed);
    static bool recent_miss;
    static int total_misses;
    static vector<int> missed_shots;
    double rolling_speed;

private:
    Color color;
    int score;
    int size;
public slots:
    /**
     * @brief VerifyCredentials: slot executes when the signal is invoked by a timer
     *
     * Deletes the virus object and alters the player score
     */
    void Expire();
};

#endif // VIRUSOBJECT_H
