#include "glview.h"
#include <QApplication>
#include <QDir>

class PresenterEmulator {
  GLview & view;
public:
  PresenterEmulator(GLview& v): view(v) {
    view.Set_game_layout(GLview::GAME_LAYOUT::MAIN_MENU);
  }



};

int main(int argc, char *argv[])
{
  setlocale(LC_ALL,"");
  QDir appDir = QFileInfo(QString::fromLocal8Bit(argv[0])).absolutePath();
  QString tmpPath = appDir.absolutePath();
  QApplication::addLibraryPath(tmpPath+"/QTplaggins");
  QApplication a(argc, argv);
  GLview w;
  PresenterEmulator presenter(w);
  return a.exec();
}
