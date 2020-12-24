#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chooseportfolio.h"
#include "homepage.h"
#include "signup.h"
#include "newspage.h"
#include "neworder.h"

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

  void hideAllPages();
  void uncheckAllTabs();

 private slots:
  void on_actionTrade_triggered();

  void on_actionHome_triggered();

  void on_actionPerformance_triggered();

  void on_actionNews_triggered();

  void on_actionMarkets_triggered();

 private:
  Ui::MainWindow *ui;

  SignUp *signUpPage;
  ChoosePortfolio *choosePortfolioPage;
  HomePage *homepage;
  NewsPage *newsPage;
  NewOrder *new_order;
  QHBoxLayout *layout;
};
#endif // MAINWINDOW_H
