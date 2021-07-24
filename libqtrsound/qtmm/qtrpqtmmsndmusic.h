#ifndef QTRPQTMMSNDMUSIC_H
#define QTRPQTMMSNDMUSIC_H

#include <QAudioOutput>
#include <qtrsndmusic.h>

class QtrpQtmmSndMusic : public QtrSndMusic
{
public:
    QtrpQtmmSndMusic();

    virtual void play() override;
    virtual void stop() override;
    virtual void pause() override;
    virtual void setVolume(int vol) override;

private:
    QAudioOutput *mOutput;
};

#endif // QTRPQTMMSNDMUSIC_H
