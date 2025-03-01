#include "UI/CMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--no-xshm");

    API::Inst().curVariant = API::Inst().getRandomVariant();
    
    QApplication a(argc, argv);
    CMainWindow w;
    w.show();
    return a.exec();
}