#ifndef QTRPSFMLAUDIOENGINE_H
#define QTRPSFMLAUDIOENGINE_H

#include "qtrpaudioengine.h"

class QtrpSfmlAudioEngine : public QtrpAudioEngine
{
public:
    QtrpSfmlAudioEngine();

    virtual QtrSndMusic *createMusic();
    virtual QtrSndSample *createSample();
};

#endif // QTRPSFMLAUDIOENGINE_H
