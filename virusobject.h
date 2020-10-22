#ifndef VIRUSOBJECT_H
#define VIRUSOBJECT_H
#include "clickablelabel.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
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
    VirusObject(VirusObject::Color c);
    static bool recent_miss;
    static int total_misses;
    static Color missed_color;

private:
    Color color;
    int score;
    int size;
public slots: void Expire();
};

#endif // VIRUSOBJECT_H
