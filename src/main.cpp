#include "glview.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
  setlocale(LC_ALL,"");
  QDir appDir = QFileInfo(QString::fromLocal8Bit(argv[0])).absolutePath();
  QString tmpPath = appDir.absolutePath();
  QApplication::addLibraryPath(tmpPath+"/QTplaggins");
  QApplication a(argc, argv);
  GLview w;
  w.show();
  return a.exec();
}
