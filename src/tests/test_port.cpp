#include "components/portfolio.h"
#include "components/trading_order.h"
#include "helper/helper.h"
#include <QtTest>
#include <QVector>
#include <iostream>



class TestPort : public QObject {
    Q_OBJECT

  public:
    TestPort();
    ~TestPort();

  private slots:
    void initTestCase();
    void cleanupTestCase();
    void testWatchlist();
    void testLoadup();
    void testSave();

  };

  TestPort::TestPort() {}

  TestPort::~TestPort() {}

  void TestPort::initTestCase() {}

  void TestPort::cleanupTestCase() {}

  void TestPort::testWatchlist(){
      Portfolio *user = new Portfolio();
      QStringList watchlist=user->getWatchList();
      user = Portfolio(1,1000, watchlist);

      QMap<std::string, QVector<double>> jsonData = user->save();
      for (auto it : jsonData.toStdMap()) {
          std::cout << it.first << " : " << std::endl ;
          std::vector<double> vect = it.second.toStdVector();
          for (std::vector<double>::const_iterator i = vect.begin(); i != vect.end(); ++i)
              std::cout << *i << ", ";
          }

      std::string s = "order";
      for (auto &c : s) {
        std::string k(1, c);
                std::string k(1, c);
        QVERIFY(typeid(jsonData[k]).name() == Enum);
        QVERIFY(jsonData[k] == TradingAction || jsonData[k] == TradingStrategy  || jsonData[k] == TradingOrderType  || jsonData[k] == TradingTiming );
      }
      std::cout << "Trading Orders updated for watchlist" << std::endl;

      user->load(jsonData);
      QJsonObject jsonDataList = user->addLoadUp();
      std::string watchData = helper::convertToString(jsonDataList);
      std::cout << watchData << std::endl;
      QVERIFY(watchData.size() != 0 && watchData != "{}");

      QVERIFY(user->getId() <2 && user->valuation()-user->getQuantity() < 40);
      std::map<std::string, std::map<long, double>> addOrder = helper::convertToMap(jsonDataList);

      for (auto it : addOrder) {
          std::cout << it.first << " :: ";
          std::map<long, double> &internal_map = it.second;
          for (auto it2: internal_map) {
                  std::cout << ",";
               std::cout << it2.first << ":" << it2.second;
          }
      }
      user->addTradingOrder();
      qDebug() << user->stock_watch_list() << endl;

      std::cout << helper::convertToFullTimeReadable(user->stock_watch_list()) << std::endl;

      delete user;
  }

  void TestPort::testLoadup(){
      LoadUp  *loaded = new LoadUp();
      loaded->load();
      qDebug() << loaded->getQuantity() << endl;
      delete loaded;
  }

  void TestPort::testSave(){
      LoadUp  *saved = new LoadUp();
      saved->save();
      qDebug() << saved->getQuantity() << endl;
      delete saved;
  }


//QTEST_APPLESS_MAIN(TestPort)

#include "tst_port.moc"