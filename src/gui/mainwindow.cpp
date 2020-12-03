#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // nav bar on the left is initialized
  LeftNavigationBar *leftNav = new LeftNavigationBar(this);
  currentTabName = "home";

  // initialize the different pages and add them to the layout
  // we add all the pages to the layout and then just hide them
  // when they are not displayed
  signUpPage = new SignUp(this);
  choosePortfolioPage = new ChoosePortfolio(this);
  homepage = new HomePage(this);
  stockDashboardPage = new StockDashboard(this);

  // connect leftNavigationBar's signals to the main window
  connect(leftNav, &LeftNavigationBar::switchTab, [this](QString tabName) {
    if (tabName != currentTabName) {
      getTabComponent(currentTabName)->hide();
      getTabComponent(tabName)->show();
    }

    currentTabName = tabName;
  });

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(leftNav);
  layout->addWidget(signUpPage);
  layout->addWidget(choosePortfolioPage);
  layout->addWidget(homepage);
  layout->addWidget(stockDashboardPage);

  signUpPage->hide();
  choosePortfolioPage->hide();
  stockDashboardPage->hide();

  ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow() {
  delete ui;
  delete leftNav;
  delete signUpPage;
  delete choosePortfolioPage;
  delete homepage;
  delete layout;
}

QWidget *MainWindow::getTabComponent(QString tabName) {
  if (tabName == "home") {
    return homepage;
  }

  if (tabName == "trade") {
    return stockDashboardPage;
  }

  return signUpPage; // placeholders for other tab names for now
}
