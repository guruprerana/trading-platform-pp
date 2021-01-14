#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);

  session = new Session();

  // initialize the different pages and add them to the layout
  // we add all the pages to the layout and then just hide them
  // when they are not displayed
  signUpPage = new SignUp(this);
  QVector <Portfolio *> portfolios = session->getPortfolios();
  choosePortfolioPage = new ChoosePortfolio(portfolios, this);
  homepage = new HomePage(this);
  newsPage = new NewsPage(this);
  new_order = new NewOrder(this);
  strategyPage = new StrategyPage(this);

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(signUpPage);
  layout->addWidget(choosePortfolioPage);
  layout->addWidget(homepage);
  layout->addWidget(newsPage);
  layout->addWidget(new_order);
  layout->addWidget(strategyPage);

  if (portfolios.size() == 0) {
    // no existing portfolios, proceed to sign up
    choosePortfolioPage->hide();
  } else {
    // we do have portfolios, proceed to choosing which
    signUpPage->hide();
  }

  homepage->hide();
  newsPage->hide();
  new_order->hide();
  strategyPage->hide();
  ui->toolBar->hide();

  ui->centralwidget->setLayout(layout);

  // connect the signals
  connect(signUpPage, &SignUp::signUpWithDetails, this,
          &MainWindow::onCreatePortfolio);
  connect(new_order, &NewOrder::newOrderCreated, this,
          &MainWindow::onCreateOrder);
  connect(choosePortfolioPage, &ChoosePortfolio::createNewPortfolio, this,
          &MainWindow::onCreateNewPortfolio);
  connect(choosePortfolioPage, &ChoosePortfolio::portfolioChosen, this,
          &MainWindow::onChoosePortfolio);
}

MainWindow::~MainWindow() {
  delete ui;
  delete session;
  delete signUpPage;
  delete choosePortfolioPage;
  delete homepage;
  delete newsPage;
  delete layout;
  delete new_order;
  delete strategyPage;
}

void MainWindow::hideAllPages() {
  homepage->hide();
  signUpPage->hide();
  choosePortfolioPage->hide();
  newsPage->hide();
  new_order->hide();
  strategyPage->hide();
}

void MainWindow::uncheckAllTabs() {
  ui->actionHome->setChecked(false);
  ui->actionTrade->setChecked(false);
  ui->actionPerformance->setChecked(false);
  ui->actionNews->setChecked(false);
  ui->actionStrategies->setChecked(false);
}

void MainWindow::on_actionHome_triggered() {
  hideAllPages();
  uncheckAllTabs();
  ui->actionHome->setChecked(true);
  homepage->show();
}

void MainWindow::on_actionTrade_triggered() {
  hideAllPages();
  uncheckAllTabs();
  ui->actionTrade->setChecked(true);
  new_order->show();
}

void MainWindow::on_actionPerformance_triggered() {
  hideAllPages();
  uncheckAllTabs();
  ui->actionPerformance->setChecked(true);
}

void MainWindow::on_actionNews_triggered() {
  hideAllPages();
  uncheckAllTabs();
  ui->actionNews->setChecked(true);
  newsPage->update();
  newsPage->show();
}

void MainWindow::on_actionStrategies_triggered() {
  hideAllPages();
  uncheckAllTabs();
  ui->actionStrategies->setChecked(true);
  strategyPage->show();
}

void MainWindow::onCreatePortfolio(QString id, qreal initialAmount,
                                   QStringList watchlist) {
  session->addPortfolio(new Portfolio(id, initialAmount, watchlist));

  // initially toolbar is hidden and shown when submit button pressed
  auto watchlistStocks = session->getCurrentWatchlistStocks();
  homepage->updateWatchlistStocks(watchlistStocks);
  strategyPage->updateWatchlistStocks(watchlistStocks);
  this->ui->toolBar->show();
  this->on_actionHome_triggered();
}

void MainWindow::onCreateOrder(TradingOrder *order) {
  Portfolio *current = session->getCurrentPortfolio();

  if (current == nullptr) {
    return;
  }

  current->addTradingOrder(order);
}

void MainWindow::onCreateNewPortfolio() {
  hideAllPages();
  uncheckAllTabs();
  ui->toolBar->hide();
  signUpPage->show();
}

void MainWindow::onChoosePortfolio(Portfolio *portfolio) {
  session->setCurrentPortfolio(portfolio);
  homepage->updateWatchlistStocks(session->getCurrentWatchlistStocks());
  this->ui->toolBar->show();
  this->on_actionHome_triggered();
}
