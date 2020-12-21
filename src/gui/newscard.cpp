#include "newscard.h"
#include "ui_newscard.h"

#include <QDebug>

NewsCard::NewsCard(QString id, QString headline, QString category,
                   QString timestamp, QString url, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::NewsCard) {
  ui->setupUi(this);

  ui->id->setText(id);
  ui->headline->setText("<a href=" + url +
                        " style=\"color:black;\" > " + headline +
                        "</a>");
  ui->headline->setTextFormat(Qt::RichText);
  ui->headline->setTextInteractionFlags(Qt::TextBrowserInteraction);
  ui->headline->setOpenExternalLinks(true);
  ui->category->setText(category);
  ui->timestamp->setText(timestamp);
}

NewsCard::~NewsCard() {
  delete ui;
}

void NewsCard::debug() {
  qDebug() << ui->id->text() << ' ' << ui->headline->text() << ' ' <<
           ui->category->text() << ' ' << ui->timestamp->text() << endl;
}
