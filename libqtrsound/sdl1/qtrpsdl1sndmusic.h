#ifndef QTRPSDL1SNDMUSIC_H
#define QTRPSDL1SNDMUSIC_H

#include <qtrsndmusic.h>
#include <SDL/SDL_mixer.h>

class QtrpSDL1SndMusic : public QtrSndMusic
{
public:
    QtrpSDL1SndMusic(QObject *parent);
    virtual ~QtrpSDL1SndMusic();

    virtual void play() override;
    virtual void stop() override;
    virtual void pause() override;
    virtual void setVolume(int vol) override;

protected:
    virtual void updateState();

private:
    Mix_Music *mHandle;
};

#endif // QTRPSDL1SNDMUSIC_H
