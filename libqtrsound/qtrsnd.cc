#include <QJsonDocument>
#include <QVariant>
#include <qtrsnd.h>
#include <qtrsndmusic.h>

#include <sdl1/qtrpsdl1audioengine.h>
#include <sfml/qtrpsfmlaudioengine.h>

QtrSnd *QtrSnd::mInstance = NULL;

//-------------------------------------------------------------------------------------------------
bool QtrSnd::init(const QString &engineoptions)
{
    destroy();
    Q_ASSERT(!mInstance);

    QVariantMap config = QJsonDocument::fromJson("{" + engineoptions.toUtf8() + "}").toVariant().toMap();
    initByJson(config);

    if (!mInstance)
        return false;

    return mInstance->mEngine->setup(config);
}

//-------------------------------------------------------------------------------------------------
void QtrSnd::destroy()
{
    if (mInstance)
        delete mInstance;
    mInstance = NULL;
}

//-------------------------------------------------------------------------------------------------
QtrSnd *QtrSnd::instance()
{
    return mInstance;
}

//-------------------------------------------------------------------------------------------------
QtrSndMusic *QtrSnd::music(const QString &localFileName)
{
    if (!mInstance || !mInstance->mEngine)
        return NULL;

    QtrSndMusic *m = mInstance->mEngine->createMusic();
    Q_ASSERT(m);
    m->setFilename(localFileName);
    return m;
}

//-------------------------------------------------------------------------------------------------
//                                             PRIVATE
//-------------------------------------------------------------------------------------------------
void QtrSnd::initByJson(const QVariantMap &config)
{
    if (config["engine"].toString() == "sdl1") {
        mInstance = new QtrSnd(new QtrpSDL1AudioEngine());
    }
    if (config["engine"].toString() == "sfml") {
        mInstance = new QtrSnd(new QtrpSfmlAudioEngine());
    }
}

//-------------------------------------------------------------------------------------------------
QtrSnd::QtrSnd(QtrpAudioEngine *engine)
 : mEngine(engine)
{
    Q_ASSERT(mEngine);
}
