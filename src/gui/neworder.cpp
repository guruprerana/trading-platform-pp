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
}

NewOrder::~NewOrder() {
  delete ui;
}

void NewOrder::computePerformanceTable(Portfolio *portfolio) {
  QVBoxLayout *tableLayout = new QVBoxLayout();

  qDebug() << "starts computing performance table " << Qt::endl;

  portfolio->computeRecordFromHistory();    // just to make sure

  qDebug() << "finishes computing performance table. starts adding rows " <<
           Qt::endl;

  QVector <QString> owned_stock = portfolio->currentOwnedStock();

  for (int id = 0; id < owned_stock.size(); id ++) {
    QString symbol = owned_stock[id];
    qDebug() << id << ' ' << symbol << Qt::endl;
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
  write(*order);
  emit newOrderCreated(order);

  setDefault();
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
  ui->estimatedValueValueLabel->setText("0");
}

void NewOrder::updateWatchlistStocks(QVector<Stock *> watchlistStocks) {
  this->watchlistStocks = watchlistStocks;

  for (auto stock : watchlistStocks) {
    ui->symbolComboBox->addItem(QString::fromStdString(stock->getSymbol()));
  }
}

void NewOrder::write(TradingOrder &trading_order) const {
  trading_order.setSymbol(ui->symbolComboBox->currentText());

  QString strategy = ui->strategyValueComboBox->currentText();
  trading_order.setStrategy(helper::QStringToQEnum<TradingOrder::TradingStrategy>
                            (strategy));

  QString actions = ui->actionsValueComboBox->currentText();
  trading_order.setAction(helper::QStringToQEnum<TradingOrder::TradingAction>
                          (actions));

  trading_order.setQuantity(ui->quantityValueSpinBox->value());

  QString order_type = ui->orderTypeValueComboBox->currentText();
  trading_order.setOrderType(
    helper::QStringToQEnum<TradingOrder::TradingOrderType>
    (order_type));

  trading_order.setLimitPrice(ui->limitPriceValueLineEdit->text().toDouble());

  QString timimg = ui->timingValueComboBox->currentText();
  trading_order.setTiming(helper::QStringToQEnum<TradingOrder::TradingTiming>
                          (timimg));

  trading_order.setTradingTime(QDateTime::currentDateTime().toTime_t());
  trading_order.setValuePerQuantity(
    ui->pricePerQuantityValueLabel->text().toDouble());
}

void NewOrder::updatePricePerQuantityAndEstimateValue() {
  Stock stock(helper::toStdString(ui->symbolComboBox->currentText()));
  qreal trade_quantity = ui->quantityValueSpinBox->value();
  qreal current_price = stock.getLatestClosedPrice();

  ui->pricePerQuantityValueLabel->setNum(current_price);
  ui->estimatedValueValueLabel->setNum(current_price * trade_quantity);
}

void NewOrder::on_symbolComboBox_currentTextChanged(const QString &symbol) {
  updatePricePerQuantityAndEstimateValue();
}

void NewOrder::on_actionsValueComboBox_currentTextChanged(
  const QString &action) {
  updatePricePerQuantityAndEstimateValue();
}

void NewOrder::on_quantityValueSpinBox_valueChanged(double quantity) {
  updatePricePerQuantityAndEstimateValue();
}
