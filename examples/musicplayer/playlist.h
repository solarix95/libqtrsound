#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QList>

class PlayList : public QObject
{
    Q_OBJECT
public:
    PlayList(QObject *parent = NULL);

    // in
    void setFiles(const QStringList &fileNames);
    void clearList();

    // out
    int     currentIndex() const;
    QString currentFile() const;
    QString fileName(int index) const;

    // misc
    void saveSettings();
    void restoreSettings();

public slots:
    void reset();
    void prev();
    void next();
    void shuffle(bool random);
    void setLoop(bool loop);

signals:
    void startReset();
    void endReset();
    void fileSelected(const QString &filename);
    void currentChanged(int index);

private:
    void setCurrentIndex(int newIndex);

    int         mCurrentIndex;
    bool        mLoop;
    bool        mShuffle;
    QStringList mFileNames;
    QList<int>  mPlayIndex;
};

#endif // PLAYLIST_H
