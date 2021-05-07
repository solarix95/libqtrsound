#ifndef QTRPSDL1AUDIOENGINE_H
#define QTRPSDL1AUDIOENGINE_H

#include "qtrpaudioengine.h"

class QtrpSDL1AudioEngine : public QtrpAudioEngine
{
public:
    QtrpSDL1AudioEngine();

    virtual bool setup(const QVariantMap &config) override;

    virtual QtrSndMusic *createMusic();
    virtual QtrSndSample *createSample();

};

#endif // QTRPSDL1AUDIOENGINE_H
