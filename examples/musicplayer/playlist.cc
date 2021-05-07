#include <QDateTime>
#include <QSettings>
#include "playlist.h"

//-------------------------------------------------------------------------------------------------
PlayList::PlayList(QObject *parent)
    : QObject(parent)
    , mCurrentIndex(-1)
    , mLoop(false)
    , mShuffle(false)
{
    qsrand(QDateTime::currentDateTime().currentMSecsSinceEpoch());
    restoreSettings();
}

//-------------------------------------------------------------------------------------------------
void PlayList::setFiles(const QStringList &fileNames)
{
    clearList();
    mFileNames = fileNames;
    reset();

}

//-------------------------------------------------------------------------------------------------
void PlayList::clearList()
{
    emit startReset();
    mFileNames.clear();
    mPlayIndex.clear();
    mCurrentIndex = -1;
    emit endReset();
}

//-------------------------------------------------------------------------------------------------
int PlayList::currentIndex() const
{
    return mCurrentIndex < 0 ? -1 : mPlayIndex[mCurrentIndex];
}

//-------------------------------------------------------------------------------------------------
QString PlayList::currentFile() const
{
    if (currentIndex() < 0)
        return QString();

    return mFileNames.at(currentIndex());
}

//-------------------------------------------------------------------------------------------------
QString PlayList::fileName(int index) const
{
    Q_ASSERT(index >= 0 && index < mFileNames.count());
    return mFileNames.at(index);
}

//-------------------------------------------------------------------------------------------------
void PlayList::saveSettings()
{
    QSettings settings;
    settings.beginGroup("Playlist");

    settings.beginWriteArray("files");

    for (int i = 0; i < mFileNames.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("fileName", mFileNames.at(i));
    }

    settings.endArray();
    settings.endGroup();

}

//-------------------------------------------------------------------------------------------------
void PlayList::restoreSettings()
{
    clearList();
    QSettings settings;
    settings.beginGroup("Playlist");

    int size = settings.beginReadArray("files");
    QStringList fileNames;
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        fileNames << settings.value("fileName").toString();
    }
    settings.endArray();
    settings.endGroup();

    setFiles(fileNames);
}

//-------------------------------------------------------------------------------------------------
void PlayList::reset()
{
    emit startReset();
    mPlayIndex.clear();

    if (mFileNames.isEmpty()) {
        mCurrentIndex = -1;
        return;
    }

    shuffle(mShuffle);
    emit endReset();
}

//-------------------------------------------------------------------------------------------------
void PlayList::prev()
{
    if (mFileNames.isEmpty())
        return;
    if (mCurrentIndex == 0) {
        if (mLoop)
            setCurrentIndex(mFileNames.count()-1);
    } else {
        setCurrentIndex(mCurrentIndex-1);
    }
}

//-------------------------------------------------------------------------------------------------
void PlayList::next()
{
    if (mFileNames.isEmpty())
        return;

    int newIndex = mCurrentIndex + 1;
    if (newIndex >= mPlayIndex.count()) {
        if (mLoop)
            setCurrentIndex(0);
    } else {
        setCurrentIndex(newIndex);
    }
}

//-------------------------------------------------------------------------------------------------
void PlayList::shuffle(bool random)
{
    if (mFileNames.isEmpty())
        return;

    mPlayIndex.clear();
    for (int i=0; i<mFileNames.count(); i++){
        mPlayIndex << i;
    }

    if (random) {
        QList<int> randomList;
        while (!mPlayIndex.isEmpty()) {
            randomList.insert(randomList.isEmpty() ? 0 : qrand() % randomList.count(),mPlayIndex.takeFirst());
        }
        mPlayIndex = randomList;
        return;
    }

    setCurrentIndex(0);
}

//-------------------------------------------------------------------------------------------------
void PlayList::setLoop(bool loop)
{
    mLoop = loop;
}

//-------------------------------------------------------------------------------------------------
void PlayList::setCurrentIndex(int newIndex)
{
    mCurrentIndex = newIndex;

    if (mCurrentIndex >= 0)
        emit currentChanged(mPlayIndex[mCurrentIndex]);
    else
        emit currentChanged(-1);

    emit fileSelected(currentFile());
}

