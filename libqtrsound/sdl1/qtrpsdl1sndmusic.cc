#include <QDebug>
#include "qtrpsdl1sndmusic.h"

//-------------------------------------------------------------------------------------------------
QtrpSDL1SndMusic::QtrpSDL1SndMusic(QObject *parent)
 : QtrSndMusic(parent)
 , mHandle(NULL)
{
}

//-------------------------------------------------------------------------------------------------
QtrpSDL1SndMusic::~QtrpSDL1SndMusic()
{
    if (mHandle)
        Mix_FreeMusic(mHandle);
}

//-------------------------------------------------------------------------------------------------
void QtrpSDL1SndMusic::play()
{
    if (isPlaying())
        return;

    if (!mHandle && !filename().isEmpty()) {
        mHandle =  Mix_LoadMUS(filename().toUtf8().constData());
        if (mHandle)
            setState(LoadedState);
    }

    if (!mHandle) {
        return;
    }
    if (state() == PauseState) {
        Mix_ResumeMusic();
        setState(PlayingState);
    } else if (Mix_PlayMusic(mHandle,1) < 0) //Music loop=1
        qWarning() << "QtrpSDL1SndMusic::play: " << Mix_GetError();
    else
        setState(PlayingState);

    // Mix_FadeInMusic(mHandle,0,5000);
}

//-------------------------------------------------------------------------------------------------
void QtrpSDL1SndMusic::stop()
{
    if (!mHandle || !isPlaying())
        return;

    Mix_HaltMusic();
    setState(StoppedState);
}

//-------------------------------------------------------------------------------------------------
void QtrpSDL1SndMusic::pause()
{
    Mix_PauseMusic();
    setState(PauseState);
}

//-------------------------------------------------------------------------------------------------
void QtrpSDL1SndMusic::setVolume(int vol)
{
    Mix_VolumeMusic(128 * (qMax(vol,qMin(vol,100))/100.0));
}

//-------------------------------------------------------------------------------------------------
void QtrpSDL1SndMusic::updateState()
{
    if (isPlaying() && (Mix_PlayingMusic() < 1))
        setState(EndedState);
}
