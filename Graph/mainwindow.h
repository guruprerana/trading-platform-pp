#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "../BACHELOR/CSE201/trading-platform-pp/src/api/api.h"
#include    "../BACHELOR/CSE201/trading-platform-pp/src/components/stock.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void clearData();
    void plot();
private slots:

  void realtimeDataSlot();

private:
    Ui::MainWindow *ui;
    QVector<double> timestamp,high;
    QTimer dataTimer;
    Stock stock=Stock("AAPL");
};

#endif // MAINWINDOW_H
