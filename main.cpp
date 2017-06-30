#include "clipboarder.h"
#include <QApplication>
#include <MyGlobalShortCut/MyGlobalShortCut.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Clipboarder w;
    w.show();

    MyGlobalShortCut *shortcut_Ctrl1 = new MyGlobalShortCut("Ctrl+1",&w);
    QObject::connect(shortcut_Ctrl1,SIGNAL(activated()),&w,SLOT(hotKey_Ctrl1()));
    MyGlobalShortCut *shortcut_Ctrl2 = new MyGlobalShortCut("Ctrl+2",&w);
    QObject::connect(shortcut_Ctrl2,SIGNAL(activated()),&w,SLOT(hotKey_Ctrl2()));
    MyGlobalShortCut *shortcut_Ctrl3 = new MyGlobalShortCut("Ctrl+3",&w);
    QObject::connect(shortcut_Ctrl3,SIGNAL(activated()),&w,SLOT(hotKey_Ctrl3()));
    MyGlobalShortCut *shortcut_Ctrl4 = new MyGlobalShortCut("Ctrl+4",&w);
    QObject::connect(shortcut_Ctrl4,SIGNAL(activated()),&w,SLOT(hotKey_Ctrl4()));
    MyGlobalShortCut *shortcut_Ctrl5 = new MyGlobalShortCut("Ctrl+5",&w);
    QObject::connect(shortcut_Ctrl5,SIGNAL(activated()),&w,SLOT(hotKey_Ctrl5()));

    return a.exec();
}
