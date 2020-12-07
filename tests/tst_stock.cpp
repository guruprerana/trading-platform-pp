#include "../src/components/stock.h"
#include "../src/helper/QJsonObjectManipulation.h"
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
    void testUpdateData();
  };

  TestStock::TestStock() {}

  TestStock::~TestStock() {}

  void TestStock::initTestCase() {}

  void TestStock::cleanupTestCase() {}

  void TestStock::testUpdateData(){
      Stock *apple = new Stock("AAPL");
      apple->updateDataByMinute();
      QJsonObject jsonDataMinute = apple->getDataByMinute();
      std::string textDataMinute = convertToJson(jsonDataMinute);
      std::cout << textDataMinute << std::endl;
      QVERIFY(textDataMinute.size() != 0 && textDataMinute != "{}");

      apple->updateDataByDay();
      QJsonObject jsonDataDay = apple->getDataByDay();
      std::string textDataDay = convertToJson(jsonDataDay);
      std::cout << textDataDay << std::endl;
      QVERIFY(textDataDay.size() != 0 && textDataDay != "{}");

      QVERIFY(apple->getLatestTimestampByDay() > 0 && apple->getLatestTimestampByDay()-apple->getLatestTimestampByMinute() < 60);
      //Verify that calling time is smaller than one minute and both functions update the current time correctly

      apple->updateNews();
      std::cout << apple->getNews() << std::endl;
  }

QTEST_APPLESS_MAIN(TestStock)

#include "tst_stock.moc"
