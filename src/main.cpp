#include "UI/CMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    API::Inst().curVariant = API::Inst().getRandomVariant();
    
    QApplication a(argc, argv);
    CMainWindow w;

    w.setWindowFlags(w.windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

    w.show();
    return a.exec();
}