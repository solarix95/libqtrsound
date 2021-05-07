#ifndef PNGPLAYER_H
#define PNGPLAYER_H

#include <QString>
#include <QImage>

class PngPlayer
{
public:
    PngPlayer(const QString &prefix);

    void next();
    const QImage &frame() const;

private:
    int           mIndex;
    QList<QImage> mFrames;
};

#endif // PNGPLAYER_H
