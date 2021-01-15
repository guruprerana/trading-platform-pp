#include "api/api.h"
#include <QtTest>
#include <iostream>

class TestAPI : public QObject {
  Q_OBJECT

public:
  TestAPI();
  ~TestAPI();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testGetStockData();
};

TestAPI::TestAPI() {}

TestAPI::~TestAPI() {}

void TestAPI::initTestCase() {}

void TestAPI::cleanupTestCase() {}

void TestAPI::testGetStockData() {
  API *api = new API();

  std::string result1 = api->getStockData("IBM", "D", 1572651390, 1572910590);
  QVERIFY(result1.size() != 0);

  std::string result2 = api->getStockData("IBM", "D", 1572651390, 1572651389);
  QVERIFY(result2 == "{\"s\":\"no_data\"}");

  std::string result3 =
      "Test HTTP code 429. The process would take some time...";
  std::cout << result3 << std::endl;
  for (int i = 0; i < 60; ++i) {
    result3 = api->getStockData("IBM", "D", 1572651390, 1572910590);
  }
  QVERIFY(result3 == ""); // "" is returned when receive HTTP code 429
}

//QTEST_APPLESS_MAIN(TestAPI)

#include "tst_api.moc"






