#include "leftnavigationbar.h"
#include "ui_leftnavigationbar.h"

LeftNavigationBar::LeftNavigationBar(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LeftNavigationBar) {
  ui->setupUi(this);
}

LeftNavigationBar::~LeftNavigationBar() {
  delete ui;
}

void LeftNavigationBar::on_homeButton_released() {
  emit switchHomeTab();
}

void LeftNavigationBar::on_tradeButton_released() {
  emit switchTradeTab();
}

void LeftNavigationBar::on_performanceButton_released() {
  emit switchPerformanceTab();
}

void LeftNavigationBar::on_newsButton_released() {
  emit switchNewsTab();
}

void LeftNavigationBar::on_marketsButton_released() {
  emit switchMarketsTab();
}
