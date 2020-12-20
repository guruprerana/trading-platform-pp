#include "neworder.h"
#include "ui_neworder.h"
#include "helper/helper.h"

NewOrder::NewOrder(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::NewOrder) {
  ui->setupUi(this);
}

NewOrder::~NewOrder() {
  delete ui;
}

void NewOrder::on_orderPushButton_released() {
  QJsonObject data;
  write(data);
  QString s = "trading-order-" + QString::number(
                QDateTime::currentDateTime().toSecsSinceEpoch()) + ".json";
  QFile save_file(s);

  if (!save_file.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  } else {
    save_file.write(QJsonDocument(data).toJson());
  }

  setDefault();
}

void NewOrder::on_cancelPushButton_pressed() {
  setDefault();
}

void NewOrder::setDefault() {
  ui->symbolValueLineEdit->setText("GOOGL");
  ui->strategyValueComboBox->setCurrentIndex(0);
  ui->actionsValueComboBox->setCurrentIndex(0);
  ui->quantityValueSpinBox->setValue(0);
  ui->orderTypeValueComboBox->setCurrentIndex(0);
  ui->limitPriceValueLineEdit->setText("0");
  ui->timingValueComboBox->setCurrentIndex(0);
  ui->estimatedValueTextBrowser->setText("0");
}

void NewOrder::write(TradingOrder &trading_order) const {
  trading_order.setSymbol(ui->symbolValueLineEdit->text());

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
  trading_order.setValuePerQuantity(0);
}

void NewOrder::write(QJsonObject &json) const {
  TradingOrder order;
  write(order);
  order.write(json);
}
