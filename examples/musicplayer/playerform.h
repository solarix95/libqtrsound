#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QString>
#include <QWidget>
#include <QIcon>
#include <QTimer>

#include <qtrsndmusic.h>

#include "playlist.h"
#include "ui_playerform.h"

class PlayerForm : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerForm(QWidget *parent = 0);
    virtual ~PlayerForm();

signals:

public slots:

protected:
    virtual void closeEvent(QCloseEvent *);

private slots:
    void playMusic();
    void playNextFile(int index);
    void stopMusic();
    void pauseMusic();
    void openFile();
    void openDir();
    void saveSettings();
    void restoreSettings();

private:
    void triggerSaveSettings();
    void setIconColor(QPushButton *widget, const QString &iconName, QColor col);

    Ui::PlayerWidget  *mUi;
    PlayList           mPlayList;
    QtrSndMusic       *mMusicHandle;
    QTimer             mSaveSettingsTimer;

};

#endif // PLAYERFORM_H
