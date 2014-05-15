#include "glview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLview w;
    w.show();
    return a.exec();
}
