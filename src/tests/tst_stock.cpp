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
    void testMap();
    void testGetDesiredMap();
    void testStrategyLinearRegression();
    void testStrategyMomentum();
    void testStrategyMovingAverage();
    void testSimulate();
    void testSentiment();

  };

  TestStock::TestStock() {}

  TestStock::~TestStock() {}

  void TestStock::initTestCase() {}

  void TestStock::cleanupTestCase() {}

  void TestStock::testUpdateData(){
//      Stock *apple = new Stock("AAPL");
//      apple->updateDataByMinute();

//      QMap<std::string, QVector<double>> jsonDataMinute = apple->getDataByMinute();
//      for (auto it : jsonDataMinute.toStdMap()) {
//          std::cout << it.first << " : " << std::endl ;
//          std::vector<double> vect = it.second.toStdVector();
//          for (std::vector<double>::const_iterator i = vect.begin(); i != vect.end(); ++i)
//              std::cout << *i << ", ";
//          }

//      std::string s = "chlot";
//      for (auto &c : s) {
//        std::string k(1, c);
//        QVERIFY(jsonDataMinute[k].size() >= 1);
//      }
//      std::cout << "Finished update data by minute" << std::endl;

//      apple->updateDataByDay();
//      QJsonObject jsonDataDay = apple->getDataByDay();
//      std::string textDataDay = helper::convertToString(jsonDataDay);
//      std::cout << textDataDay << std::endl;
//      QVERIFY(textDataDay.size() != 0 && textDataDay != "{}");

//      QVERIFY(apple->getLatestTimestampByDay() > 0 && apple->getLatestTimestampByDay()-apple->getLatestTimestampByMinute() < 60);
//      //Verify that calling time is smaller than one minute and both functions update the current time correctly
//      std::map<std::string, std::map<long, double>> mapDataDay = helper::convertToMap(jsonDataDay);

//      for (auto it : mapDataDay) {
//          std::cout << it.first << " :: ";
//          std::map<long, double> &internal_map = it.second;
//          for (auto it2: internal_map) {
//                  std::cout << ",";
//               std::cout << it2.first << ":" << it2.second;
//          }
//      }
//      apple->updateNews();
//      qDebug() << apple->getNews() << endl;

//      std::cout << helper::convertToFullTimeReadable(apple->getLatestTimestampByDay()) << std::endl;

//      delete apple;
  }

  void TestStock::testNewsClass(){
//      News *markets = new News();
//      markets->updateMarketNews();
//      qDebug() << markets->getMarketNews() << endl;
  }

  void TestStock::testMap(){
//      Stock *apple = new Stock("AAPL");
//      std::string linear = "LR";
//      std::string c = "c";
//      Strategy *strat = new Strategy(linear, apple, false, c);
//      std::cout << strat->get_name() << "; ";
//      std::cout << strat->get_price_type() << "; ";
//      std::cout << strat->get_stock()->getSymbol() << "; ";
//      //Testing the map
//      strat->set_map_six_months();
//      std::map<long, double> map_six_months = strat->get_map_six_months();
//      std::cout << "Size of the map is "<< map_six_months.size();
//      std::cout << "{";
//      for (auto it : map_six_months){
//          std::cout << it.first << " : " << it.second << ", ";
//      }
//      std::cout << "}";


  }

  void TestStock::testGetDesiredMap(){
//      Stock *apple = new Stock("AAPL");
//      std::string linear = "LR";
//      std::string c = "c";
//      Strategy *strat = new Strategy(linear, apple, false, c);
//      strat->set_map_six_months();
//      std::map<int, double> desired_map = strat->get_desired_map(30,7);
//      std::cout << "{";
//      for (auto it : desired_map){
//          std::cout << it.first << " : " << it.second << ", ";
//      }
//      std::cout << "}";



  }

  void TestStock::testStrategyLinearRegression() {
//      Stock *apple = new Stock("AAPL");
//      std::string linear = "LR";
//      std::string o = "o";
//      Strategy *strat = new Strategy(linear, apple, false, o);
//      //Testing slope and y intercept of auxiliary_linear_regression
//      //The output is correct: I've tested the function in python with the same input data using polyfit and the output is the same
//      strat->set_map_six_months();
//      std::map<int, double> map = strat->get_desired_map(strat->get_map_six_months().size());
//      auto res = strat->auxiliary_linear_regression(map); //we fit the data over the lasst six months
//      double slope = std::get<0>(res);
//      double yintercept = std::get<1>(res);
//      std::cout <<"slope = "<< slope << " ; ";
//      std::cout <<"yintercept = " <<yintercept;

//      //Tells to buy or not and the percentage
//      std::cout<< "Output";
//      auto res2 = strat->calculate_signals();
//      std::cout<< std::get<0>(res2);
//      std::cout<< std::get<1>(res2);
  }

  void TestStock::testStrategyMomentum(){
//      Stock *nvda = new Stock("NVDA");
//      std::string mom = "MOM";
//      std::string c = "c";
//      Strategy *strat = new Strategy(mom, nvda, false, c);
//      strat->set_map_six_months();
//      std::map<int, double> cache;
//      for (int k=0; k<4; k++){
//          std::map<int, double> bars_10 = strat->get_desired_map(9,k);
//          std::map<int, double> bars_5 = strat->get_desired_map(4,k);
//          double sma_10 = strat->calculate_sma(bars_10);
//          double sma_5 = strat->calculate_sma(bars_5);
//          std::cout << "   k = " << k << " ;  ";
//          std::cout << "sma10 = " << sma_10 << " ;  ";
//          std::cout << "sma5 = " << sma_5 << " ;  ";
//          std::cout << "res = " << sma_5/sma_10;
//          double moment = sma_5/sma_10;
//          cache.insert(std::pair<int, double>(k, moment));

//      }
//      std::cout << "aux =   " << strat->auxiliary_momentum(cache);
//      //if the momentum for the k=0 is strictly less than 1, it should return (0, 1);


//      //Tells to buy or not and the percentage
//      std::cout<< "Output";
//      auto res2 = strat->calculate_signals();
//      std::cout<< std::get<0>(res2);
//      std::cout<< std::get<1>(res2);

 }

  void TestStock::testStrategyMovingAverage(){
//      Stock *apple = new Stock("AAPL");
//      std::string ema = "EMA";
//      std::string c = "c";
//      Strategy *strat = new Strategy(ema, apple, false, c);
//      strat->set_map_six_months();

//      //Tells to buy or not and the percentage
//      std::cout<< "Output";
//      auto res2 = strat->calculate_signals();
//      std::cout<< std::get<0>(res2)<< " ; ";
//      std::cout<< std::get<1>(res2) << " ; ";
  }
  void TestStock::testSimulate(){
//      Stock *apple = new Stock("AAPL");
//      std::string mom = "MOM";
//      std::string c = "c";
//      Strategy *strat = new Strategy(mom, apple, false, c);
//      strat->set_map_six_months();
//      auto res = strat->simulate();
//      QVector<long> timeseries = std::get<0>(res);
//      QVector<double> strat_output = std::get<1>(res);
//      std::cout << timeseries.size();
//      std::cout<< strat_output.size();
//      std::cout << "Vector of timestamp: {";
//      for (QVector<long>::iterator i= timeseries.begin(); i != timeseries.end(); i++){
//          std::cout << (*i) <<",";
//      }

//      std::cout << "}    Vector of outputs of momentums {";
//      for (QVector<double>::iterator i= strat_output.begin(); i != strat_output.end(); i++){
//          std::cout << (*i) <<",";
//      }

      Stock *apple = new Stock("AAPL");
      std::string linear = "LR";
      std::string c = "c";
      Strategy *strat = new Strategy(linear, apple, false, c);
      strat->set_map_six_months();
      std::map<int, double> map = strat->get_desired_map(strat->get_map_six_months().size());
      auto res1 = strat->auxiliary_linear_regression(map); //we fit the data over the lasst six months
      double slope = std::get<0>(res1);
      double yintercept = std::get<1>(res1);
      std::cout <<"slope = "<< slope << " ; ";
      std::cout <<"yintercept = " <<yintercept;

      auto res = strat->simulate();
      QVector<long> timeseries = std::get<0>(res);
      QVector<double> strat_output = std::get<1>(res);
      std::cout << timeseries.size();
      std::cout<< strat_output.size();
      std::cout << "Vector of timestamp: {";
      for (QVector<long>::iterator i= timeseries.begin(); i != timeseries.end(); i++){
          std::cout << (*i) <<",";
      }

      std::cout << "}    Vector of points fitted by LR {";
      for (QVector<double>::iterator i= strat_output.begin(); i != strat_output.end(); i++){
          std::cout << (*i) <<",";
      }
  }

  void TestStock::testSentiment(){
//      Stock *apple = new Stock("AAPL");
//      apple->updateSentimentData();
//      qDebug() << apple->getSentimentData() << endl;
  }


QTEST_APPLESS_MAIN(TestStock)

#include "tst_stock.moc"
