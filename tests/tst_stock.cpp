#include "../src/components/stock.h"
#include <QtTest>
#include <iostream>


class TestStock : public QObject {
    Q_OBJECT

  public:
    TestStock();
    ~TestStock();

  private slots:
    void initTestCase();
    void cleanupTestCase();
    void testUpdateDataByDay();
  };

  TestStock::TestStock() {}

  TestStock::~TestStock() {}

  void TestStock::initTestCase() {}

  void TestStock::cleanupTestCase() {}

  void TestStock::testUpdateDataByDay(){
      Stock *apple = new Stock("AAPL");
      apple->updateDataByMinute();
      QJsonObject jsonDataMinute = apple->getDataByMinute();
      QJsonDocument docMinute(jsonDataMinute);
      QString strJsonMinute(docMinute.toJson(QJsonDocument::Compact));
      std::string textDataMinute = strJsonMinute.toUtf8().constData();
      std::cout << textDataMinute << std::endl;
      QVERIFY(textDataMinute.size() != 0);

      apple->updateDataByDay();
      QJsonObject jsonDataDay = apple->getDataByDay();
      QJsonDocument docDay(jsonDataDay);
      QString strJsonDay(docDay.toJson(QJsonDocument::Compact));
      std::string textDataDay = strJsonDay.toUtf8().constData();
      std::cout << textDataDay << std::endl;
      QVERIFY(textDataDay.size() != 0);
  }

QTEST_APPLESS_MAIN(TestStock)

#include "tst_stock.moc"
