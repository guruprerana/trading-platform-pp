#include "components/trading_order.h"
#include "helper/helper.h"
#include <QtTest>
#include <iostream>
#include <typeinfo>

class TestTrade : public QObject {
  Q_OBJECT

public:
  TestTrade();
  ~TestTrade();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testWrite();
};

TestTrade::TestTrade() {}

TestTrade::~TestTrade() {}

void TestTrade::initTestCase() {}

void TestTrade::cleanupTestCase() {}

void TestTrade::testWrite() {
  TradingOrder *trade = new TradingOrder();
  QMap<std::string, QVector<double>> jsonData=trade->write(TradingAction, TradingStrategy , TradingOrderType, TradingTiming);

  for (auto it : jsonData.toStdMap()) {
          std::cout << it.first << " : " << std::endl ;
          std::vector<double> vect = it.second.toStdVector();
          for (std::vector<double>::const_iterator i = vect.begin(); i != vect.end(); ++i)
              std::cout << *i << ", ";
          }

      for (auto &c : s) {
        std::string k(1, c);
        QVERIFY(typeid(jsonData[k]).name() == Enum);
        QVERIFY(jsonData[k] == TradingAction || jsonData[k] == TradingStrategy  || jsonData[k] == TradingOrderType  || jsonData[k] == TradingTiming );

      }
}

//QTEST_APPLESS_MAIN(TestTrade)

#include "tst_trade.moc"