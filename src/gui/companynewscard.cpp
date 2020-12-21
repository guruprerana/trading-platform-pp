#include "companynewscard.h"
#include "ui_companynewscard.h"
#include <QDebug>

CompanyNewsCard::CompanyNewsCard(QString headline, QString url,
                                 QString timestamp,
                                 QString summary, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CompanyNewsCard) {
  ui->setupUi(this);

  ui->headline->setText("<a href=" + url +
                        " style=\"color:rgb(70,70,70);\" > " + headline +
                        "</a>");
  ui->headline->setTextFormat(Qt::RichText);
  ui->headline->setTextInteractionFlags(Qt::TextBrowserInteraction);
  ui->headline->setOpenExternalLinks(true);
  ui->timestamp->setText(timestamp);
  ui->summary->setText(summary);
}

CompanyNewsCard::~CompanyNewsCard() {
  delete ui;
}

void CompanyNewsCard::debug() {
  qDebug() << ui->headline->text() << ' ' << ui->timestamp->text() << ' ' <<
           ui->summary->text() << endl;
}
