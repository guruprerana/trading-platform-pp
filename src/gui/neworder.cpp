#include "neworder.h"
#include "ui_neworder.h"
#include "helper/helper.h"
#include "./widgets/stockperformancerow.h"

#include <QString>

NewOrder::NewOrder(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::NewOrder) {
  ui->setupUi(this);

  // Sets signals to self
//  connect(this, &NewOrder::newOrderCreated, this,
//          &NewOrder::computePerformanceTable);

  QVBoxLayout *tableLayout = new QVBoxLayout();

  for (int i = 0; i < 10; i++) {
    tableLayout->addWidget(new StockPerformanceRow);
  }

  QWidget *widget = new QWidget();
  widget->setLayout(tableLayout);
  ui->tableScroll->setWidget(widget);

  ui->errorLabel->hide();
}

NewOrder::~NewOrder() {
  delete ui;
}

void NewOrder::computePerformanceTable(Portfolio *portfolio) {
  QVBoxLayout *tableLayout = new QVBoxLayout();

  qDebug() << "starts computing performance table " << endl;

  portfolio->computeRecordFromHistory();    // just to make sure

  qDebug() << "finishes computing performance table. starts adding rows " <<
           endl;

  QVector <QString> owned_stock = portfolio->currentOwnedStock();

  for (int id = 0; id < owned_stock.size(); id ++) {
    QString symbol = owned_stock[id];
    qDebug() << id << ' ' << symbol << endl;
    StockPerformanceRow *row = new StockPerformanceRow;
    row->from(portfolio, id, symbol);
    tableLayout->addWidget(row);
  }

  QWidget *widget = new QWidget();
  widget->setLayout(tableLayout);
  ui->tableScroll->setWidget(widget);

  return;
}

void NewOrder::on_orderPushButton_released() {
  TradingOrder *order = new TradingOrder();

  if (write(*order)) {
    emit newOrderCreated(order);
    setDefault();
  }
}

void NewOrder::on_cancelPushButton_pressed() {
  setDefault();
}

void NewOrder::setDefault() {
  ui->strategyValueComboBox->setCurrentIndex(0);
  ui->actionsValueComboBox->setCurrentIndex(0);
  ui->quantityValueSpinBox->setValue(0);
  ui->orderTypeValueComboBox->setCurrentIndex(0);
  ui->limitPriceValueLineEdit->setText("0");
  ui->timingValueComboBox->setCurrentIndex(0);
  ui->estimatedValueTextBrowser->setText("0");
}

void NewOrder::updateWatchlistStocks(QVector<Stock *> watchlistStocks) {
  this->watchlistStocks = watchlistStocks;

  for (auto stock : watchlistStocks) {
    ui->symbolComboBox->addItem(QString::fromStdString(stock->getSymbol()));
  }
}



bool NewOrder::write(TradingOrder &trading_order) {
  trading_order.setSymbol(ui->symbolComboBox->currentText());

  QString strategy = ui->strategyValueComboBox->currentText();
  trading_order.setStrategy(helper::QStringToQEnum<TradingOrder::TradingStrategy>
                            (strategy));

  if (trading_order.getStrategy() != TradingOrder::TradingStrategy::ETF) {
    setErrorText("We only support ETF for now.");
    return false;
  }

  QString actions = ui->actionsValueComboBox->currentText();
  trading_order.setAction(helper::QStringToQEnum<TradingOrder::TradingAction>
                          (actions));

  if (trading_order.getAction() == TradingOrder::TradingAction::SellShort) {
    setErrorText("We do not support selling short yet.");
    return false;
  }

  trading_order.setQuantity(ui->quantityValueSpinBox->value());

  if (trading_order.getQuantity() <= 0) {
    setErrorText("Quantity needs to be greater than 0.");
    return false;
  }

  QString order_type = ui->orderTypeValueComboBox->currentText();
  trading_order.setOrderType(
    helper::QStringToQEnum<TradingOrder::TradingOrderType>
    (order_type));

  if (trading_order.getOrderType() !=
      TradingOrder::TradingOrderType::MarketOrder) {
    setErrorText("We only support market orders for now.");
    return false;
  }

  trading_order.setLimitPrice(ui->limitPriceValueLineEdit->text().toDouble());

  if (trading_order.getLimitPrice() > 0) {
    setErrorText("We do not support limit prices yet.");
    return false;
  }

  QString timimg = ui->timingValueComboBox->currentText();
  trading_order.setTiming(helper::QStringToQEnum<TradingOrder::TradingTiming>
                          (timimg));

  if (trading_order.getTiming() !=
      TradingOrder::TradingTiming::DayOnly) {
    setErrorText("We only support immediate buying or selling currently (Day Oly timing).");
    return false;
  }

  trading_order.setTradingTime(QDateTime::currentDateTime().toTime_t());
  trading_order.setValuePerQuantity(0);

  return true;
}

void NewOrder::setErrorText(QString error) {
  ui->errorLabel->setText(error);
}

void NewOrder::updateEstimatedValue() {
  Stock *stock;
  QString symbol = ui->symbolComboBox->currentText();

  for (auto s : watchlistStocks) {
    if (s->getSymbol().compare(symbol.toStdString()) == 0) {
      stock = s;
    }
  }

  if (stock == nullptr) {
    return;
  }

  qreal currentPrice = stock->getLatestClosedPrice();
  ui->estimatedValueTextBrowser->setText(QString::number(currentPrice *
                                         ui->quantityValueSpinBox->value()));
}

void NewOrder::on_symbolComboBox_activated(const QString &arg1) {
  updateEstimatedValue();
}

void NewOrder::on_quantityValueSpinBox_valueChanged(double arg1) {
  updateEstimatedValue();
}
