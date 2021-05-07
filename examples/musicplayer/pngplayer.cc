#include <QFile>
#include "pngplayer.h"

PngPlayer::PngPlayer(const QString &prefix)
{
    int index = 0;
    while (QFile::exists(QString("%1-%2.png").arg(prefix).arg(index))) {
        mFrames << QImage(QString("%1-%2.png").arg(prefix).arg(index));
        index++;
    }
    mIndex = 0;
}

void PngPlayer::next()
{
    mIndex++;
    if (mIndex >= mFrames.count())
        mIndex = 0;
}

const QImage &PngPlayer::frame() const
{
    Q_ASSERT(mIndex >= 0 && mIndex < mFrames.count());
    return mFrames[mIndex];
}
