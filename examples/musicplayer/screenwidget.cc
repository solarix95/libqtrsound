#include <QTimer>
#include <QPainter>
#include "screenwidget.h"

//-------------------------------------------------------------------------------------------------
ScreenWidget::ScreenWidget(QWidget *parent)
    : QWidget(parent)
    , mRunning(false)
    , mPngPlayer(":/animation/frame")

{
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [&]() {
        if (!mRunning)
            return;
        mPngPlayer.next();
        update();
    });

    t->start(1000/20); // 20fps
}

//-------------------------------------------------------------------------------------------------
void ScreenWidget::setState(bool running)
{
    mRunning = running;
}

//-------------------------------------------------------------------------------------------------
void ScreenWidget::setFilename(const QString &filename)
{
    mFilename = filename;
    update();
}

//-------------------------------------------------------------------------------------------------
void ScreenWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(),Qt::black);

    p.setRenderHint(QPainter::HighQualityAntialiasing,true);
    p.setRenderHint(QPainter::SmoothPixmapTransform,true);
    p.setPen(Qt::green);
    p.drawImage(rect(),mPngPlayer.frame());
    p.drawText(rect(),Qt::AlignCenter,mFilename);
}

