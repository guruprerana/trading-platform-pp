#include "nodatapage.h"
#include "ui_nodatapage.h"

NoDataPage::NoDataPage(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::NoDataPage)
{
  ui->setupUi(this);
}

NoDataPage::~NoDataPage()
{
  delete ui;
}
