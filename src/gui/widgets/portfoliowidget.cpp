#include "portfoliowidget.h"
#include "ui_portfoliowidget.h"

PortfolioWidget::PortfolioWidget(Portfolio *portfolio, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PortfolioWidget) {
  ui->setupUi(this);

  this->portfolio = portfolio;

  ui->portfolioName->setText(portfolio->getId());
}

PortfolioWidget::~PortfolioWidget() {
  delete ui;
}

void PortfolioWidget::on_portfolioName_released() {
  emit portfolioClicked(portfolio);
}
