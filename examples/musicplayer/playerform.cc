#include <qtrsnd.h>
#include "playerform.h"
#include <QFileDialog>
#include <QSettings>
#include <QImage>

//-------------------------------------------------------------------------------------------------
PlayerForm::PlayerForm(QWidget *parent)
    : QWidget(parent)
    , mUi(NULL)
    , mMusicHandle(NULL)
{
    mUi = new Ui::PlayerWidget();
    mUi->setupUi(this);

    connect(mUi->btnOpen, &QPushButton::pressed, this, &PlayerForm::openFile);
    connect(mUi->btnPlay, &QPushButton::pressed, this, &PlayerForm::playMusic);
    connect(mUi->btnStop, &QPushButton::pressed, this, &PlayerForm::stopMusic);
    connect(mUi->btnPause, &QPushButton::pressed, this, &PlayerForm::pauseMusic);
    connect(mUi->btnNext, &QPushButton::pressed, &mPlayList, &PlayList::next);
    connect(mUi->btnPrev, &QPushButton::pressed, &mPlayList, &PlayList::prev);

    connect(mUi->verticalSlider, &QSlider::valueChanged, this, [&](int) {
        triggerSaveSettings();
        if (!mMusicHandle)
            return;
        mMusicHandle->setVolume(mUi->verticalSlider->value());

    });

    connect(mUi->btnShuffle, &QPushButton::pressed, this, [&]() {
        mPlayList.shuffle(!mUi->btnShuffle->isChecked());
    });

    connect(mUi->btnLoop, &QPushButton::pressed, this, [&]() {
        mPlayList.setLoop(!mUi->btnShuffle->isChecked());
    });

    connect(&mPlayList, &PlayList::currentChanged, this, &PlayerForm::playNextFile);
    connect(&mPlayList, &PlayList::fileSelected, mUi->screen, &ScreenWidget::setFilename);

    connect(&mSaveSettingsTimer, &QTimer::timeout, this, &PlayerForm::saveSettings);
    mSaveSettingsTimer.setSingleShot(true);
    mSaveSettingsTimer.setInterval(100);

    QFile style(":/dark-style.css");
    style.open(QIODevice::ReadOnly);
    setStyleSheet(style.readAll());

    setIconColor(mUi->btnPlay,":/icons/icons8-play-48.png",Qt::white);
    setIconColor(mUi->btnStop,":/icons/icons8-stop-48.png",Qt::white);
    setIconColor(mUi->btnPause,":/icons/icons8-pause-48.png",Qt::white);
    setIconColor(mUi->btnNext,":/icons/icons8-end-48.png",Qt::white);
    setIconColor(mUi->btnPrev,":/icons/icons8-skip-to-start-48.png",Qt::white);


    setIconColor(mUi->btnShuffle,":/icons/icons8-shuffle-48.png",Qt::white);
    setIconColor(mUi->btnLoop,":/icons/icons8-repeat-48.png",Qt::white);

    setIconColor(mUi->btnOpen,":/icons/icons8-file-48.png",Qt::white);

    restoreSettings();
}

//-------------------------------------------------------------------------------------------------
PlayerForm::~PlayerForm()
{
    stopMusic();
    delete mUi;
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::closeEvent(QCloseEvent *)
{
    saveSettings();
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::playMusic()
{
    if (mMusicHandle) {
        mMusicHandle->play();
        return;
    }

    if (mPlayList.currentFile().isEmpty())
        return;

    mMusicHandle = QtrSnd::music(mPlayList.currentFile());
    if (!mMusicHandle)
        return;

    mMusicHandle->setVolume(mUi->verticalSlider->value());
    connect(mMusicHandle, &QtrSndMusic::stateChanged, this, [&](int state) {
        mUi->screen->setState(state == QtrSndMusic::PlayingState);
        if (state == QtrSndMusic::EndedState)
            mPlayList.next();
    });
    mMusicHandle->play();
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::playNextFile(int index)
{
    if (index < 0)
        return;
    stopMusic();
    playMusic();
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::stopMusic()
{
    if (!mMusicHandle)
        return;
    mMusicHandle->stop();
    mMusicHandle->deleteLater();
    mMusicHandle = NULL;
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::pauseMusic()
{
    if (!mMusicHandle)
        return;
    mMusicHandle->pause();
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::openFile()
{
    QStringList userSelection = QFileDialog::getOpenFileNames(this,trUtf8("Open"),mPlayList.currentFile());
    if (userSelection.isEmpty())
        return;

    mPlayList.setFiles(userSelection);
    triggerSaveSettings();
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::openDir()
{
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::saveSettings()
{
    mPlayList.saveSettings();
    QSettings settings;
    settings.setValue("volume",mUi->verticalSlider->value());
    settings.setValue("shuffle",mUi->btnShuffle->isChecked());
    settings.setValue("loop",mUi->btnLoop->isChecked());
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::restoreSettings()
{
    mPlayList.restoreSettings();

    QSettings settings;

    mUi->verticalSlider->setValue(settings.value("volume",70).toInt());
    mUi->btnShuffle->setChecked(settings.value("shuffle",false).toBool());
    mUi->btnLoop->setChecked(settings.value("loop",false).toBool());
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::triggerSaveSettings()
{
    mSaveSettingsTimer.start();
}

//-------------------------------------------------------------------------------------------------
void PlayerForm::setIconColor(QPushButton *widget, const QString &iconName, QColor col)
{
    Q_ASSERT(widget);

    QImage img(iconName);
    Q_ASSERT(!img.isNull());

    for (int x=0; x<img.width(); x++) {
        for (int y=0; y<img.height(); y++) {
            if (qAlpha(img.pixel(x,y)) == 0)
                continue;
            QColor newColor(col);
            newColor.setAlpha(qAlpha(img.pixel(x,y)));
            img.setPixel(x,y,newColor.rgba());
        }
    }
    widget->setIcon(QIcon(QPixmap::fromImage(img)));
}

