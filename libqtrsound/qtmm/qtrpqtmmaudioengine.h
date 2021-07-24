#ifndef QTRPQTMMAUDIOENGINE_H
#define QTRPQTMMAUDIOENGINE_H

#include <QAudioOutput>
#include "qtrpaudioengine.h"

class QtrpQtmmAudioEngine : public QtrpAudioEngine
{
public:
    QtrpQtmmAudioEngine();

    virtual bool setup(const QVariantMap &config) override;

    virtual QtrSndMusic *createMusic();
    virtual QtrSndSample *createSample();

private:
    QAudioOutput *mOutput;
};

#endif // QTRPQTMMAUDIOENGINE_H
