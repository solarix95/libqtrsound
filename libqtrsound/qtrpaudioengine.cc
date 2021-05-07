#include "qtrpaudioengine.h"

QtrpAudioEngine::QtrpAudioEngine(QObject *parent) : QObject(parent)
{

}

bool QtrpAudioEngine::setup(const QVariantMap &)
{
    return true;
}

bool QtrpAudioEngine::hasError() const
{
    return false;
}

