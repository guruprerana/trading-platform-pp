#include "components/stock.h"
#include "components/news.h"
#include "helper/helper.h"
#include "recommendation/strategy.h"
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
    void testGetData();
    void testStrategyLinearRegression();
    void testStrategyMomentum();
    void testStrategyMovingAverage();
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
      std::cout << "ba";

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
      std::cout << apple->getNews() << std::endl;

      std::cout << helper::convertToFullTimeReadable(apple->getLatestTimestampByDay()) << std::endl;
  }

  void TestStock::testNewsClass(){
      News *markets = new News();
      markets->updateMarketNews();
      qDebug() << markets->getMarketNews() << endl;
  }

  void TestStock::testGetData(){
      Stock *apple = new Stock("AAPL");
      std::string linear = "LR";
      std::string c = "c";
      Strategy *strat = new Strategy(linear, apple, false, c);
      std::cout << strat->get_name() << "; ";
      std::cout << strat->get_price_type() << "; ";
      std::cout << strat->get_stock()->getSymbol() << "; ";
      //Testing the map
      std::map<long, double> map = strat->get_data(20);
      for (auto it : map) {
          std::cout << it.first << " : "<< it.second << ";  ";
      }
  }

  void TestStock::testStrategyLinearRegression() {
      Stock *apple = new Stock("AAPL");
      std::string linear = "LR";
      std::string c = "c";
      Strategy *strat = new Strategy(linear, apple, false, c);
      //Testing slope and y intercept of auxiliary_linear_regression
      //The output is correct: I've tested the function in python with the same input data using polyfit and the output is the same
      std::map<long, double> map = strat->get_data(20);
      auto res = strat->auxiliary_linear_regression(map);
      double slope = std::get<0>(res);
      double yintercept = std::get<1>(res);
      std::cout <<"slope"<< slope << " ; ";
      std::cout << yintercept;

      //Tells to buy or not and the percentage
      std::cout<< "Output";
      auto res2 = strat->calculate_signals();
      std::cout<< std::get<0>(res2);
      std::cout<< std::get<1>(res2);
  }

  void TestStock::testStrategyMomentum(){
      Stock *apple = new Stock("AAPL");
      std::string linear = "MOM";
      std::string c = "c";
      Strategy *strat = new Strategy(linear, apple, false, c);

      //Tells to buy or not and the percentage
      std::cout<< "Output";
      auto res2 = strat->calculate_signals();
      std::cout<< std::get<0>(res2);
      std::cout<< std::get<1>(res2);
  }

  void TestStock::testStrategyMovingAverage(){
      Stock *apple = new Stock("AAPL");
      std::string linear = "EMA";
      std::string c = "c";
      Strategy *strat = new Strategy(linear, apple, false, c);

      //Tells to buy or not and the percentage
      std::cout<< "Output";
      auto res2 = strat->calculate_signals();
      std::cout<< std::get<0>(res2);
      std::cout<< std::get<1>(res2);
  }

QTEST_APPLESS_MAIN(TestStock)

#include "tst_stock.moc"
