#include "gui/mainwindow.h"

#include <QApplication>
#include <QIODevice>
#include <QLocale>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::Europe));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
