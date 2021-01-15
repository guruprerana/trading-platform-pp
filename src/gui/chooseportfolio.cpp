#include "chooseportfolio.h"
#include "ui_chooseportfolio.h"
#include "./widgets/portfoliowidget.h"

ChoosePortfolio::ChoosePortfolio(QVector<Portfolio *> &portfolios,
                                 QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ChoosePortfolio) {
  ui->setupUi(this);

  this->portfolios = portfolios;

  layout = new QHBoxLayout();

  for (Portfolio *portfolio : portfolios) {
    PortfolioWidget *widget = new PortfolioWidget(portfolio, this);
    layout->addWidget(widget);
    connect(widget, &PortfolioWidget::portfolioClicked, [this, portfolio]() {
      emit portfolioChosen(portfolio);
    });
  }

  QWidget *widget = new QWidget();
  widget->setLayout(layout);
  ui->scrollArea->setWidget(widget);
}

ChoosePortfolio::~ChoosePortfolio() {
  delete ui;
  delete layout;
}

void ChoosePortfolio::on_pushButton_released() {
  emit createNewPortfolio();
}
