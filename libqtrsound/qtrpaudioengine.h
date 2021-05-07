#ifndef QTRPAUDIOENGINE_H
#define QTRPAUDIOENGINE_H

#include <QObject>
#include <QVariantMap>

class QtrSndMusic;
class QtrSndSample;

class QtrpAudioEngine : public QObject
{
    Q_OBJECT
public:
    explicit QtrpAudioEngine(QObject *parent = 0);

    // Initialization, status
    virtual bool setup(const QVariantMap &config);
    virtual bool hasError() const;

    // Factory
    virtual QtrSndMusic *createMusic()   = 0;
    virtual QtrSndSample *createSample() = 0;

signals:

public slots:
};

#endif // QTRPAUDIOENGINE_H
