#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // initialize the different pages and add them to the layout
  // we add all the pages to the layout and then just hide them
  // when they are not displayed
  signUpPage = new SignUp(this);
  connect(signUpPage, &SignUp::signUpWithDetails, [this]() {
    // initially toolbar is hidden and shown when submit button pressed
    this->ui->toolBar->show();
    this->on_actionHome_triggered();
  });

  choosePortfolioPage = new ChoosePortfolio(this);
  homepage = new HomePage(this);
  newsPage = new NewsPage(this);
  new_order = new NewOrder(this);

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(signUpPage);
  layout->addWidget(choosePortfolioPage);
  layout->addWidget(homepage);
  layout->addWidget(newsPage);
  layout->addWidget(new_order);

  homepage->hide();
  choosePortfolioPage->hide();
  newsPage->hide();
  new_order->hide();
  ui->toolBar->hide();

  ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow() {
  delete ui;
  delete signUpPage;
  delete choosePortfolioPage;
  delete homepage;
  delete newsPage;
  delete layout;
  delete new_order;
}

void MainWindow::hideAllPages() {
  homepage->hide();
  signUpPage->hide();
  choosePortfolioPage->hide();
  newsPage->hide();
  new_order->hide();
}

void MainWindow::uncheckAllTabs() {
  ui->actionHome->setChecked(false);
  ui->actionTrade->setChecked(false);
  ui->actionPerformance->setChecked(false);
  ui->actionNews->setChecked(false);
  ui->actionMarkets->setChecked(false);
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

void MainWindow::on_actionMarkets_triggered() {
  hideAllPages();
  uncheckAllTabs();
  ui->actionMarkets->setChecked(true);
}
