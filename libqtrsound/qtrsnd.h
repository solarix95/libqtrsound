#ifndef QTR_SND_H
#define QTR_SND_H

#include <QObject>
#include <QVariantMap>

class QtrSndMusic;
class QtrSndSample;
class QtrpAudioEngine;

class QtrSnd : public QObject
{
    Q_OBJECT
public:

    static bool    init(const QString &engineoptions);
    static void    destroy();
    static QtrSnd* instance();

    // Player
    static QtrSndMusic  *music(const QString &localFileName);
    static QtrSndSample *sample(const QString &localSampleFile);

private:
    static void initByJson(const QVariantMap &config);

    QtrSnd(QtrpAudioEngine *engine);

    static QtrSnd   *mInstance;
    QtrpAudioEngine *mEngine;
};

#endif
