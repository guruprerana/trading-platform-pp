#include "gui/mainwindow.h"

#include <QApplication>
#include <QIODevice>
#include <QLocale>
#include <QTextStream>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
