
#include <QDebug>
#include "qtrpsdl1audioengine.h"
#include "qtrpsdl1sndmusic.h"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

//-------------------------------------------------------------------------------------------------
QtrpSDL1AudioEngine::QtrpSDL1AudioEngine()
{
}

//-------------------------------------------------------------------------------------------------
bool QtrpSDL1AudioEngine::setup(const QVariantMap &config)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        qWarning() << "QtrpSDL1AudioEngine::SDL_Init " << SDL_GetError();
        return false;
    }

    int     frequency  = config.value("frequency","44100").toInt();
    quint16 format     = config.value("format",AUDIO_S16).toInt();
    int     channels   = config.value("channels",2).toInt();
    int     chunksize  = config.value("chunksize",256).toInt();

    if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0) {
        qWarning() << "QtrpSDL1AudioEngine::Mix_OpenAudio" << Mix_GetError();
        return false;
    }

    return true;
}

//-------------------------------------------------------------------------------------------------
QtrSndMusic *QtrpSDL1AudioEngine::createMusic()
{
    return new QtrpSDL1SndMusic(this);
}

//-------------------------------------------------------------------------------------------------
QtrSndSample *QtrpSDL1AudioEngine::createSample()
{
    return NULL;
}

