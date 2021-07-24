#include <QApplication>

#include "playerform.h"

#include <qtrsnd.h>
#include <qtrsndmusic.h>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    QCoreApplication::setOrganizationName("Snowland");
    // QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Musicplayer");

    // QtrSnd::init("\"engine\" : \"sdl1\"");
    QtrSnd::init("\"engine\" : \"sfml\"");

    PlayerForm player;
    player.show();

    return app.exec();
}
