#ifndef QTRPSFMLSNDMUSIC_H
#define QTRPSFMLSNDMUSIC_H

#include <qtrsndmusic.h>
#include <SFML/Audio.hpp>

class QtrpSfmlSndMusic : public QtrSndMusic
{
public:
    QtrpSfmlSndMusic(QObject *parent);

    virtual void play();
    virtual void stop();
    virtual void pause();

    virtual void setVolume(int vol);

private:
    sf::Music mHandle;
};

#endif // QTRPSFMLSNDMUSIC_H
