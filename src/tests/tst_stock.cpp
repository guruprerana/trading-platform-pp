#include "components/stock.h"
#include "components/news.h"
#include "helper/helper.h"
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
    void testNewsClass();
  };

  TestStock::TestStock() {}

  TestStock::~TestStock() {}

  void TestStock::initTestCase() {}

  void TestStock::cleanupTestCase() {}

  void TestStock::testUpdateData(){
      Stock *apple = new Stock("AAPL");
      apple->updateDataByMinute();
      QJsonObject jsonDataMinute = apple->getDataByMinute();
      std::string textDataMinute = helper::convertToString(jsonDataMinute);
      std::cout << textDataMinute << std::endl;
      QVERIFY(textDataMinute.size() != 0 && textDataMinute != "{}");

      apple->updateDataByDay();
      QJsonObject jsonDataDay = apple->getDataByDay();
      std::string textDataDay = helper::convertToString(jsonDataDay);
      std::cout << textDataDay << std::endl;
      QVERIFY(textDataDay.size() != 0 && textDataDay != "{}");

      QVERIFY(apple->getLatestTimestampByDay() > 0 && apple->getLatestTimestampByDay()-apple->getLatestTimestampByMinute() < 60);
      //Verify that calling time is smaller than one minute and both functions update the current time correctly
      std::map<std::string, std::map<long, double>> mapDataDay = helper::convertToMap(jsonDataDay);

      for (auto it : mapDataDay) {
          std::cout << it.first << " : ";
          std::map<long, double> &internal_map = it.second;
          for (auto it2: internal_map) {
                  std::cout << ",";
               std::cout << it2.first << ":" << it2.second;
          }
      }
      apple->updateNews();
      std::cout << apple->getNews() << std::endl;

      std::cout << helper::convertToFullTimeReadable(apple->getLatestTimestampByDay()) << std::endl;
  }

  void TestStock::testNewsClass(){
      News *markets = new News();
      markets->updateMarketNews();
      qDebug() << markets->getMarketNews() << endl;
  }


QTEST_APPLESS_MAIN(TestStock)

#include "tst_stock.moc"
