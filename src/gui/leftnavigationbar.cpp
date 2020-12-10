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
  emit switchTab(QString("home"));
}

void LeftNavigationBar::on_tradeButton_released() {
  emit switchTab(QString("trade"));
}

void LeftNavigationBar::on_performanceButton_released() {
  emit switchTab(QString("performance"));
}

void LeftNavigationBar::on_newsButton_released() {
  emit switchTab(QString("news"));
}

void LeftNavigationBar::on_marketsButton_released() {
  emit switchTab(QString("markets"));
}
