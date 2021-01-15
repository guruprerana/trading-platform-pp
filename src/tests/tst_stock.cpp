#include "components/stock.h"
#include "components/news.h"
#include "helper/helper.h"
#include "recommendation/strategy.h"
#include <QtTest>
#include <QVector>
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
    void testSentiment();

  };

  TestStock::TestStock() {}

  TestStock::~TestStock() {}

  void TestStock::initTestCase() {}

  void TestStock::cleanupTestCase() {}

  void TestStock::testUpdateData(){
      Stock *apple = new Stock("AAPL");
      apple->updateDataByMinute();

      QMap<std::string, QVector<double>> jsonDataMinute = apple->getDataByMinute();
      for (auto it : jsonDataMinute.toStdMap()) {
          std::cout << it.first << " : " << std::endl ;
          std::vector<double> vect = it.second.toStdVector();
          for (std::vector<double>::const_iterator i = vect.begin(); i != vect.end(); ++i)
              std::cout << *i << ", ";
          }

      std::string s = "chlot";
      for (auto &c : s) {
        std::string k(1, c);
        QVERIFY(jsonDataMinute[k].size() >= 1);
      }
      std::cout << "Finished update data by minute" << std::endl;

      apple->updateDataByDay();
      QJsonObject jsonDataDay = apple->getDataByDay();
      std::string textDataDay = helper::convertToString(jsonDataDay);
      std::cout << textDataDay << std::endl;
      QVERIFY(textDataDay.size() != 0 && textDataDay != "{}");

      QVERIFY(apple->getLatestTimestampByDay() > 0 && apple->getLatestTimestampByDay()-apple->getLatestTimestampByMinute() < 60);
      //Verify that calling time is smaller than one minute and both functions update the current time correctly
      std::map<std::string, std::map<long, double>> mapDataDay = helper::convertToMap(jsonDataDay);

      for (auto it : mapDataDay) {
          std::cout << it.first << " :: ";
          std::map<long, double> &internal_map = it.second;
          for (auto it2: internal_map) {
                  std::cout << ",";
               std::cout << it2.first << ":" << it2.second;
          }
      }
      apple->updateNews();
      qDebug() << apple->getNews() << endl;

      std::cout << helper::convertToFullTimeReadable(apple->getLatestTimestampByDay()) << std::endl;

      delete apple;
  }

  void TestStock::testNewsClass(){
      News *markets = new News();
      markets->updateMarketNews();
      qDebug() << markets->getMarketNews() << endl;
      delete markets;
  }

  void TestStock::testSentiment(){
      Stock *apple = new Stock("AAPL");
      apple->updateSentimentData();
      qDebug() << apple->getSentimentData() << endl;
      QJsonObject sentiment = apple->getSentimentData()["sentiment"].toObject();
      qDebug() << sentiment << endl;
      delete apple;
  }


QTEST_APPLESS_MAIN(TestStock)

#include "tst_stock.moc"
