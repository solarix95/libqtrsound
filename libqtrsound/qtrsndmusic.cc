#include <QTimer>
#include "qtrsndmusic.h"


QtrSndMusic::QtrSndMusic(QObject *parent)
    : QObject(parent)
    , mFilename()
    , mState(UndefState)
{
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &QtrSndMusic::updateState);
    t->start(100);
}

QtrSndMusic::~QtrSndMusic()
{
}

void QtrSndMusic::setVolume(int vol)
{
}

void QtrSndMusic::setState(QtrSndMusic::State newState)
{
    if (mState == newState)
        return;
    mState = newState;
    emit stateChanged(mState);
}


void QtrSndMusic::updateState()
{

}
