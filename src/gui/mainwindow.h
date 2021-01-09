#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chooseportfolio.h"
#include "homepage.h"
#include "signup.h"
#include "newspage.h"
#include "neworder.h"
#include "strategypage.h"

#include <QMainWindow>
#include <QBoxLayout>
#include <QString>
#include <QStringList>
#include "../components/session.h"
#include "../components/portfolio.h"
#include "../components/stock.h"

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

  void on_actionStrategies_triggered();

 private:
  Ui::MainWindow *ui;
  Session *session;

  SignUp *signUpPage;
  ChoosePortfolio *choosePortfolioPage;
  HomePage *homepage;
  NewsPage *newsPage;
  NewOrder *new_order;
  StrategyPage *strategyPage;
  QHBoxLayout *layout;

 private slots:
  void onCreatePortfolio(QString id, qreal initialAmount, QStringList watchlist);
  void onCreateOrder(TradingOrder *order);
};
#endif // MAINWINDOW_H
