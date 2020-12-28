#ifndef NODATAPAGE_H
#define NODATAPAGE_H

#include <QWidget>

namespace Ui {
class NoDataPage;
}

class NoDataPage : public QWidget
{
  Q_OBJECT

  public:
  explicit NoDataPage(QWidget *parent = nullptr);
  ~NoDataPage();

  private:
  Ui::NoDataPage *ui;
};

#endif // NODATAPAGE_H
