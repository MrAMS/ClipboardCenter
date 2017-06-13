#include "clipboarder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Clipboarder w;
    w.show();

    return a.exec();
}
