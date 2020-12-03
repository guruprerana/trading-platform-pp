#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chooseportfolio.h"
#include "homepage.h"
#include "leftnavigationbar.h"
#include "signup.h"
#include "stockdashboard.h"

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

  QWidget *getTabComponent(QString tabName);

 private:
  QString currentTabName;
  Ui::MainWindow *ui;

  LeftNavigationBar *leftNav;
  SignUp *signUpPage;
  ChoosePortfolio *choosePortfolioPage;
  HomePage *homepage;
  StockDashboard *stockDashboardPage;
  QHBoxLayout *layout;
};
#endif // MAINWINDOW_H
