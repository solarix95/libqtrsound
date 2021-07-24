#include <QAudioDeviceInfo>
#include "qtrpqtmmaudioengine.h"

//-------------------------------------------------------------------------------------------------
QtrpQtmmAudioEngine::QtrpQtmmAudioEngine()
 : mOutput(nullptr)
{   
}

//-------------------------------------------------------------------------------------------------
bool QtrpQtmmAudioEngine::setup(const QVariantMap &config)
{
    QAudioDeviceInfo::defaultOutputDevice();

}

//-------------------------------------------------------------------------------------------------
QtrSndMusic *QtrpQtmmAudioEngine::createMusic()
{
}

//-------------------------------------------------------------------------------------------------
QtrSndSample *QtrpQtmmAudioEngine::createSample()
{
}

