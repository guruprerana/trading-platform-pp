#include "signalcard.h"
#include "ui_signalcard.h"
#include "helper/helper.h"

SignalCard::SignalCard(double timestamp, bool buy, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SignalCard) {
  ui->setupUi(this);

  ui->date->setText(QString(helper::convertToReadable(
                              (long)timestamp).c_str()));
  ui->signal->setText(buy ? "BUY" : "SELL");
  ui->signal->setStyleSheet(buy ? "color:green" : "color:red");
}

SignalCard::~SignalCard() {
  delete ui;
}
