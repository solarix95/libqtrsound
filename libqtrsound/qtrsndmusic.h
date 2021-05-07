#ifndef QTRSNDMUSIC_H
#define QTRSNDMUSIC_H

#include <QString>
#include <QObject>

class QtrSndMusic : public QObject
{
    Q_OBJECT
public:
    enum State {
        UndefState,
        LoadedState,
        PlayingState,
        EndedState,
        StoppedState,
        PauseState
    };

    explicit QtrSndMusic(QObject *parent = 0);
    virtual ~QtrSndMusic();

    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    virtual void setVolume(int vol);

    inline void  setFilename(const QString &aFilename)       { mFilename = aFilename ;       }
    inline const QString &filename() const                   { return mFilename;             }
    inline bool  isPlaying() const                           { return mState == PlayingState;}
    inline State state() const                               { return mState;                }

signals:
    void stateChanged(int newState);

public slots:

protected slots:
    void setState(State newState);

    virtual void updateState();

private:
    QString mFilename;
    State   mState;
};

#endif // QTRSNDMUSIC_H
