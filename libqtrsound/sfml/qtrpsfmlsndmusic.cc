#include "qtrpsfmlsndmusic.h"

QtrpSfmlSndMusic::QtrpSfmlSndMusic(QObject *parent)
 : QtrSndMusic(parent)
{
}

//-------------------------------------------------------------------------------------------------
void QtrpSfmlSndMusic::play()
{
    if (isPlaying())
        return;

    if (!mHandle.openFromFile(filename().toUtf8().data()))
        return;

    mHandle.play();
    setState(PlayingState);
}

//-------------------------------------------------------------------------------------------------
void QtrpSfmlSndMusic::stop()
{
    mHandle.stop();
    setState(StoppedState);
}

//-------------------------------------------------------------------------------------------------
void QtrpSfmlSndMusic::pause()
{
    mHandle.pause();
    setState(PauseState);
}

//-------------------------------------------------------------------------------------------------

void QtrpSfmlSndMusic::setVolume(int vol)
{
    mHandle.setVolume(vol);
}

