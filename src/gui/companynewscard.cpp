#include "companynewscard.h"
#include "ui_companynewscard.h"
#include <QDebug>

CompanyNewsCard::CompanyNewsCard(QString id, QString headline, QString url,
                                 QString timestamp,
                                 QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CompanyNewsCard) {
  ui->setupUi(this);

  ui->id->setText(id);
  ui->headline->setText("<a href=" + url +
                        " style=\"color:black;\" > " + headline +
                        "</a>");
  ui->headline->setTextFormat(Qt::RichText);
  ui->headline->setTextInteractionFlags(Qt::TextBrowserInteraction);
  ui->headline->setOpenExternalLinks(true);
  ui->timestamp->setText(timestamp);
}

CompanyNewsCard::~CompanyNewsCard() {
  delete ui;
}

void CompanyNewsCard::debug() {
  qDebug() << ui->headline->text() << ' ' << ui->timestamp->text() << endl;
}
