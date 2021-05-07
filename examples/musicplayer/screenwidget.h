#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>
#include <QString>
#include "pngplayer.h"

class ScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenWidget(QWidget *parent = 0);

signals:

public slots:
    void setState(bool running);
    void setFilename(const QString &filename);

protected:
    void paintEvent(QPaintEvent *);

private:
    bool      mRunning;
    QString   mFilename;
    PngPlayer mPngPlayer;
};

#endif // SCREENWIDGET_H
