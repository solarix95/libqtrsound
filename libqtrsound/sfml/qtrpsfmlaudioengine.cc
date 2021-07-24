#include "qtrpsfmlaudioengine.h"
#include "qtrpsfmlsndmusic.h"

QtrpSfmlAudioEngine::QtrpSfmlAudioEngine()
{

}

QtrSndMusic *QtrpSfmlAudioEngine::createMusic()
{
    return new QtrpSfmlSndMusic(this);
}

QtrSndSample *QtrpSfmlAudioEngine::createSample()
{
    return NULL;
}

