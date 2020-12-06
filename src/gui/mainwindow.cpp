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
  new_order = new NewOrder(this);

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
  layout->addWidget(new_order);

  signUpPage->hide();
  choosePortfolioPage->hide();
  new_order->hide();

  ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow() {
  delete ui;
  delete leftNav;
  delete signUpPage;
  delete choosePortfolioPage;
  delete homepage;
  delete layout;
  delete new_order;
}

QWidget *MainWindow::getTabComponent(QString tabName) {
  if (tabName == "home")
    return homepage;
  else if (tabName == "trade"){
    return new_order;
  }
  else 
    return homepage;  // place holder for other tab names
}
