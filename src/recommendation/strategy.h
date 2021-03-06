#ifndef STRATEGY_H
#define STRATEGY_H
#include "../components/stock.h"
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <QVector>
using std::string;
using std::map;

class Strategy {
 public:
  Strategy();
  Strategy(std::string strategy_name, Stock *stock, bool data_by_minute,
           std::string price_type);
  ~Strategy();
  void set_stock(Stock *stock);
  void set_name(std::string strategy_name);
  Stock *get_stock();
  std::string get_name();
  std::string get_price_type();

  void update_stock_data();
  void calculate_sma(int interval, QVector<double> &timestamp_sma,
                     QVector<double> &price_sma);
  void calculate_ema(int interval, QVector<double> &timestamp_ema,
                     QVector<double> &price_ema);
  void calculate_mom(QVector<double> &timestamp_mom,
                     QVector<double> &price_mom);
  void calculate_signals_sma();
  void calculate_signals_ema();
  void calculate_signals_mom();
  void calculate_signals_lr();
  void calculate_lr(int interval, QVector<double> &timestamp_lr,
                    QVector<double> &slope, QVector<double> &intercept);
  double compute_average_key(int i, int interval);
  double compute_average_value(int i, int interval);

  int auxiliary_momentum(const QVector<double> &price_mom, int i);

  void simulate();

//  //Handling maps of data
//  void set_map_six_months();
//  std::map<long, double> get_map_six_months();
//  std::map<int, double> get_desired_map(int N,
//                                        int k = 0); //Returns a map with only the elements we need from the data member map_data

//  //Auxiliary functions use to make recommandation
//  double calculate_sma(std::map<int, double> &bars);
//  double calculate_ema(std::map<int, double> &bars);
//  int auxiliary_momentum(std::map<int, double> &cache);
//  bool exponential_moving_average();
//  double compute_average_value(std::map<int, double> &bars);
//  double compute_average_key(std::map<int, double> &bars);
//  std::tuple<double, double> auxiliary_linear_regression(std::map<int, double>
//      &bars);
//  bool linear_regression();
//  std::tuple<bool, double> momentum();

//  //Makes the recommandation : buy or sell or nothing and the percentage
//  std::tuple<bool, double> calculate_signals();

  //Returns the vectors used for the plots


 public:
  // Data members
  std::string strategy_name;
  Stock *stock; // stock under consideration
  bool data_by_minute;
  std::string
  price_type; // price_type is a lower case string in ['o','c','h','l','v']
  std::string str1 = "EMA";
  std::string str2 = "MOM";
  std::string str3 = "LR";
  std::string str4 = "SMA";
  QVector<double> timestamp;
  QVector<double> price;
  QVector<double> timestamp_sma50;
  QVector<double> timestamp_sma20;
  QVector<double> price_sma50;
  QVector<double> price_sma20;
  QVector<double> timestamp_ema11;
  QVector<double> price_ema11;
  QVector<double> timestamp_ema6;
  QVector<double> price_ema6;
  QVector<QPair<double, bool>> signals_sma;
  QVector<QPair<double, bool>> signals_ema;
  QVector<double>timestamp_mom;
  QVector<QPair<double, QPair<double, bool>>> signals_mom;
  QVector<double>price_mom;

  QVector<double>timestamp_sma10;
  QVector<double>timestamp_sma5;
  QVector<double>price_sma10;
  QVector<double>price_sma5;

  QVector<double>slope;
  QVector<QPair<double, bool>>signals_lr;
  QVector<double>intercept;
  QVector<double>timestamp_lr;



};


#endif // STRATEGY_H

