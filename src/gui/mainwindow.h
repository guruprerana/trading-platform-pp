#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chooseuser.h"
#include "homepage.h"
#include "leftnavigationbar.h"
#include "signup.h"

#include <QMainWindow>
#include <qboxlayout.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

  LeftNavigationBar *leftNav;
  SignUp *signUpPage;
  ChooseUser *chooseUserPage;
  HomePage *homepage;
  QHBoxLayout *layout;
};
#endif // MAINWINDOW_H
