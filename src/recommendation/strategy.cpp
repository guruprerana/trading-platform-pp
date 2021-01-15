#include "strategy.h"
#include "../components/stock.h"
#include "../helper/helper.cpp"
#include "../helper/helper.h"
#include <string>
#include <tuple>
#include <map>
#include <cmath>
#include <iostream>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVector>

using std::string;
using std::map;

Strategy::Strategy() {
  data_by_minute = true;
  this->strategy_name = "None";
  this->stock = nullptr;
  this->data_by_minute = false; //by default it is by day
  this->price_type = "c"; // by default consider closing price
}

Strategy::Strategy(std::string strategy_name,
                   Stock *stock,
                   bool data_by_minute = false,
                   std::string price_type = "c") {
  this->strategy_name =
    strategy_name; //possible names {'MOM', 'SMA', 'EMA', 'LR'}
  this->stock = stock;
  this->data_by_minute = data_by_minute; //if false, the data is provided by day
  this->price_type = price_type;
  update_stock_data();
}

Strategy::~Strategy() {
  delete stock;
}

void Strategy::set_stock(Stock *stock) {
  this->stock = stock;
  update_stock_data();
}

void Strategy::set_name(std::string strategy_name) {
  this->strategy_name = strategy_name;
}

Stock *Strategy::get_stock() {
  return this->stock;

}
std::string Strategy::get_name() {
  return  this->strategy_name;
}
std::string Strategy::get_price_type() {
  return  this->price_type;
}

void Strategy::update_stock_data() {
  stock->updateDataByDay();
  auto jsonObject = stock->getDataByDay();
  timestamp = helper::convert_to_vector(jsonObject, "t");
  price = helper::convert_to_vector(jsonObject, price_type);
  assert(timestamp.size() == price.size());

  timestamp_sma20.clear();
  timestamp_sma50.clear();
  price_sma20.clear();
  price_sma50.clear();
  signals_sma.clear();

  timestamp_ema11.clear();
  price_ema11.clear();
  timestamp_ema6.clear();
  price_ema6.clear();
  signals_ema.clear();

  timestamp_mom.clear();
  signals_mom.clear();
  price_mom.clear(); // list of momentum
  timestamp_sma10.clear();
  timestamp_sma5.clear();
  price_sma10.clear();
  price_sma5.clear();

  slope.clear();
  signals_lr.clear();
  intercept.clear();
  timestamp_lr.clear();
}

void Strategy::calculate_mom(QVector<double> &timestamp_mom,
                             QVector<double> &price_mom) {
  if (!timestamp_mom.isEmpty()) {
    return;
  }

  calculate_sma(10, timestamp_sma10, price_sma10);
  calculate_sma(5, timestamp_sma5, price_sma5);

  int sz10 = price_sma10.size();
  int sz5 = price_sma10.size();

  for (int i = 0; i < sz10 ; ++i) {
    double moment = price_sma5[i + sz5 - sz10] / price_sma10[i];
    timestamp_mom.append(timestamp_sma10[i]);
    price_mom.append(moment);
  }
}

void Strategy::calculate_signals_mom() {
  if (!price_mom.isEmpty()) {
    return;
  }

  calculate_mom(timestamp_mom, price_mom);
  int szmom = price_mom.size();

  for (int i = 3; i < szmom; ++i) {
    int action = auxiliary_momentum(price_mom, i);

    if (action == 0) {
      signals_mom.append({timestamp_mom[i], {1.0, false}});
      //return std::make_tuple(false, 1.0);
    } else if (action == -1) {
      signals_mom.append({timestamp_mom[i], {0.8, true}});
    } else if (action == 1) {
      signals_mom.append({timestamp_mom[i], {1.0, true}});
    }
  }
}

int Strategy::auxiliary_momentum(const QVector<double> &price_mom, int i) {
  if (price_mom[i] < 1) {
    return 0;
  }

  double diff1 = price_mom[i - 3] - price_mom[i - 2];
  double diff2 = price_mom[i - 1] - price_mom[i];

  if (diff1 <= diff2) {
    return 1;
  } else {
    return -1;
  }
}



void Strategy::calculate_sma(int interval, QVector<double> &timestamp_sma,
                             QVector<double> &price_sma) {
  if (!timestamp_sma.isEmpty() || !price_sma.isEmpty()) {
    return;
  }

  double sum = 0;

  for (int i = 0; i < price.size(); ++i) {
    sum += price[i];

    if (i >= interval) {
      sum -= price[i - interval];
    }

    if (i < interval - 1) {
      continue;
    }

    timestamp_sma.append(timestamp[i]);
    price_sma.append(sum / interval);
  }
}

void Strategy::calculate_signals_sma() {
  if (!timestamp_sma20.isEmpty() || !timestamp_sma50.isEmpty()) {
    return;
  }

  calculate_sma(20, timestamp_sma20, price_sma20);
  calculate_sma(50, timestamp_sma50, price_sma50);

  int sz20 = price_sma20.size();
  int sz50 = price_sma50.size();

  for (int i = 1; i < sz50; ++i) {
    if (price_sma20[i + sz20 - sz50] > price_sma50[i] &&
        price_sma20[i + sz20 - sz50 - 1] < price_sma50[i - 1]) {
      signals_sma.append({timestamp_sma50[i], true}); // buy signal
    }

    if (price_sma20[i + sz20 - sz50] < price_sma50[i] &&
        price_sma20[i + sz20 - sz50 - 1] > price_sma50[i - 1]) {
      signals_sma.append({timestamp_sma50[i], false}); // sell signal
    }
  }
}

void Strategy::calculate_ema(int interval, QVector<double> &timestamp_ema,
                             QVector<double> &price_ema) {
  if (!timestamp_ema.isEmpty() || !price_ema.isEmpty()) {
    return;
  }

  double smoothing_parameter = 0.4; //decay factor of terms in Moving Average

  for (int i = interval - 1; i < price.size(); ++i) {
    double e_MovingAverage = 0;
    int weight_factor = 0; // degree of the smoothing_parameter for a given summand

    for (int j = i - interval + 1; j <= i; ++j) {
      e_MovingAverage += smoothing_parameter * (std::pow((1 - smoothing_parameter),
                         weight_factor)) * price[j];
      weight_factor += 1;
    }

    timestamp_ema.append(timestamp[i]);
    price_ema.append(e_MovingAverage);
  }
}

bool compare_interval_smaller(const QVector<double> &a,
                              const QVector<double> &b, int ia, int ib, int interval) {
  // check if a[ia-interval+1] < b[ib-interval+1], ..., a[ia] < b[ib]
  while (interval > 0 && ia >= 0 && ib >= 0) {
    if (a[ia] >= b[ib]) {
      return false;
    }

    --ia;
    --ib;
    --interval;
  }

  return true;
}

void Strategy::calculate_signals_ema() {

  if (!timestamp_ema6.isEmpty() || !timestamp_ema11.isEmpty()) {
    return;
  }

  calculate_ema(6, timestamp_ema6, price_ema6);
  calculate_ema(11, timestamp_ema11, price_ema11);
  int sz6 = price_ema6.size();
  int sz11 = price_ema11.size();

  for (int i = 1; i < sz11; ++i) {
    if (compare_interval_smaller(
          price_ema6, price_ema11, i - sz11 + sz6 - 1, i - 1, 3) &&
        price_ema6[i - sz11 + sz6] > price_ema11[i]) {
      signals_ema.append({timestamp_ema11[i], true}); // buy signal
    }

    if (compare_interval_smaller(
          price_ema11, price_ema6, i - 1, i - sz11 + sz6 - 1, 3) &&
        price_ema11[i] > price_ema6[i - sz11 + sz6]) {
      signals_ema.append({timestamp_ema11[i], false}); // sell signal
    }
  }

}


void Strategy::calculate_signals_lr() {
  if (!signals_lr.isEmpty()) {
    return;
  }

  calculate_lr(10, timestamp_lr, slope, intercept);

  for (int i = 1; i < slope.size(); i ++) {
    if (slope[i] <= 0) {
      signals_lr.append({timestamp_lr[i], false});
    } else {
      signals_lr.append({timestamp_lr[i], true});
    }
  }


}

void Strategy::calculate_lr(int interval, QVector<double> &timestamp_lr,
                            QVector<double> &slope, QVector<double> &intercept) {
  if (!slope.isEmpty()) {
    return;
  }

  for (int i = interval; i < price.size(); ++i) {
    double value_average = this->compute_average_value(i, interval);
    double key_average = this->compute_average_key(i, interval);
    double sum_prod = 0;
    double sum_square = 0;

    for (int j = 0; j < interval; j++) {
      sum_prod += timestamp[i -  j] * price[i - j];
      sum_square += timestamp[i -  j] * timestamp[i -  j];
    }

    double ss_xx = sum_square - (key_average * key_average * interval);
    double ss_xy = sum_prod - (key_average * value_average * interval);
    double slope_lr = ss_xy / ss_xx;
    double yintercept = value_average - (slope_lr * key_average);
    slope.append(slope_lr);
    intercept.append(yintercept);
    timestamp_lr.append(timestamp[i]);

  }

}

double Strategy::compute_average_key(int i, int interval) {
  double key_average = 0;

  for (int j = 0; j < interval; j++) {
    key_average += timestamp[i - j];
  }

  return (key_average / interval);
}

double Strategy::compute_average_value(int i, int interval) {
  double value_average = 0;

  for (int j = 0; j < interval; j++) {
    value_average += price[i - j];
  }

  return (value_average / interval);
}




////Set map  {time:price} of the stock over the last 6 months: the first element is for today and the last is for six months ago
//void Strategy::set_map_six_months() {
//  this->stock->updateDataByDay();
//  QJsonObject jsonData = this->stock->getDataByDay();

//  std::map<std::string, std::map<long, double>> mapData = helper::convertToMap(
//        jsonData);
//  //converts the QJsonObject with the data of the last 6 months into a std::map<std::string, std::map<long, double>> {price_type : {time:price}}

//  this->map_six_months =
//    mapData[this->get_price_type()]; //take the map <long, double> associated to the price_type chosen at the beginning
//}

////Returns the data member "map_data"
//std::map<long, double> Strategy::get_map_six_months() {
//  return this->map_six_months;
//}

////Return a map for the last n days of starting from k days ago (k=0 for today, k=1 for yesterday...)
////You must call at least once set_map_six_months() before calling the function
//std::map<int, double> Strategy::get_desired_map(int N, int k) {
//  std::map<int, double> res;
//  int count = 0;
//  int map_index = 0;

//  for (auto it : map_six_months) {
//    if (count >= k && count < N + k) {
//      res[map_index] =
//        it.second; //here the key of the map is set to be 0,1,... because it is easier to compute the slope
//      //for the linear regression and other strategies don't use the key only the value of the map
//      map_index += 1;
//    }

//    if (count == N + k) {
//      return res;
//    }

//    count += 1;
//  }

//  return res;
//}

//bool Strategy::exponential_moving_average() {

//  std::map<int, double> bars_11 = this->get_desired_map(11);
//  std::map<int, double> bars_6 = this->get_desired_map(6);
//  double ema_11 = this->calculate_ema(bars_11); // Longer Moving Average
//  double ema_06 = this->calculate_ema(bars_6);  // Shorter Moving Average
//  double markup = 0.05;// markup introduces anticipation into our strategy:

//  if (ema_06 > (1 - markup)*ema_11) {
//    return true;
//  } else if (ema_11 > (1 + markup)*ema_06) {
//    return false;
//  }

//  return false;
//}


//// Calculate Simple Moving Average
//double Strategy::calculate_sma(std::map<int, double> &bars) {
//  double sum = 0;

//  for (auto &it : bars) {
//    sum += it.second;
//  }

//  return sum / bars.size();
//}


//// Calculate Exponential Moving Average
//double Strategy::calculate_ema(std::map<int, double> &bars) {
//  assert(!bars.empty());
//  double e_MovingAverage = 0;
//  double smoothing_parameter = 0.4; //decay factor of terms in Moving Average
//  int weight_factor = 0; // degree of the smoothing_parameter for a given summand

//  for (auto &it : bars) {
//    e_MovingAverage += smoothing_parameter * (std::pow((1 - smoothing_parameter),
//                       weight_factor)) * it.second;
//    weight_factor += 1;
//  }

//  return e_MovingAverage;
//}


//int Strategy::auxiliary_momentum(std::map<int, double> &cache) {
////1-full, 0-sell, -1-perc
//  if (cache.at(0) < 1) {
//    return 0;
//  }

//  double diff1 = cache.at(3) - cache.at(2);
//  double diff2 = cache.at(1) - cache.at(0);

//  if (diff1 <= diff2) {
//    return 1;
//  } else {
//    return -1;
//  }
//}

//std::tuple<bool, double> Strategy::momentum() {
//  std::map<int, double> cache;

//  for (int k = 0; k < 4; k++) {
//    std::map<int, double> bars_10 = this->get_desired_map(9, k);
//    std::map<int, double> bars_5 = this->get_desired_map(4, k);
//    double sma_10 = this->calculate_sma(bars_10);
//    double sma_5 = this->calculate_sma(bars_5);
//    double moment = sma_5 / sma_10;
//    cache.insert(std::pair<int, double>(k, moment));
//  }

//  int action = this->auxiliary_momentum(cache);

//  if (action == 0) {
//    return std::make_tuple(false, 1.0);
//  } else if (action == -1) {
//    return std::make_tuple(true, 0.8);
//  }

//  if (action == 1) {
//    return std::make_tuple(true, 1.0);

//  }
//}

//double Strategy::compute_average_key(std::map<int, double> &bars) {
//  double key_average = 0;

//  for (auto item : bars) {
//    key_average += item.first;
//  }

//  return (key_average / bars.size());
//}

//double Strategy::compute_average_value(std::map<int, double> &bars) {
//  double value_average = 0;

//  for (auto item : bars) {
//    value_average += item.second;
//  }

//  return (value_average / bars.size());
//}

//std::tuple<double, double> Strategy::auxiliary_linear_regression(
//  std::map<int, double> &bars) {
//  assert(!bars.empty());
//  double value_average = this->compute_average_value(bars); // value = price = y
//  double key_average = this->compute_average_key(bars); //key = time = x
//  double sum_prod = 0;
//  double sum_square = 0;

//  for (auto item : bars) {
//    sum_prod += item.first * item.second;
//    sum_square += item.first * item.first;
//  }

//  double ss_xx = sum_square - (key_average * key_average * bars.size());
//  double ss_xy = sum_prod - (key_average * value_average * bars.size());
//  double slope = ss_xy / ss_xx;
//  double intercept = value_average - (slope * key_average);
//  return std::make_tuple(slope,
//                         intercept); //use the slope and the y-intercept in the plot of simulate

//}

//bool Strategy::linear_regression() {
//  int nb_points = this->get_map_six_months().size();
//  std::map<int, double> bars = this->get_desired_map(nb_points);
//  auto res = this->auxiliary_linear_regression(bars);
//  double slope = std::get<0>(res);

//  if (slope <= 0) {
//    return false;
//  } else {
//    return true;
//  }
//}



//std::tuple<bool, double> Strategy::calculate_signals() {
//  bool bought;
//  double percentage = 1.0;
//  //provides outcome of the chosen strategy
//  std::string name = this->get_name();

//  if (this->str1.compare(name) == 0) { //exponential moving average
//    bought =  this->exponential_moving_average();
//  }

//  if (this->str2.compare(name) == 0) {
//    auto res = this->momentum();
//    bought = std::get<0>(res);
//    percentage = std::get<1>(res);
//  }

//  if (this->str3.compare(name) == 0) { //linear regression
//    bought = this->linear_regression();
//  }

//  return std::make_tuple(bought, percentage);
//}

void Strategy::simulate() {
//  int nb_points =
//    this->get_map_six_months().size(); // number of points in our plot for the last six months = size of Qvector = size of map_six_months
  std::string name = this->get_name();

  if (this->str1.compare(name) == 0) { //exponential moving average
    return this->calculate_signals_ema();
//    for (int k = 0; k < nb_points; k++) {
//      std::map<int, double> bars_6 = this->get_desired_map(6, k);
//      double ema_06 = this->calculate_ema(bars_6);
//      strategy_output.prepend(ema_06);
//    }
  }

//  if (this->str2.compare(name) == 0) { //momentum
//    for (int k = 0; k < nb_points; k++) {
//      std::map<int, double> bars_10 = this->get_desired_map(9, k);
//      std::map<int, double> bars_5 = this->get_desired_map(4, k);
//      double sma_10 = this->calculate_sma(bars_10);
//      double sma_5 = this->calculate_sma(bars_5);
//      double moment = sma_5 / sma_10;
//      strategy_output.prepend(moment);
//    }
//  }

//  if (this->str3.compare(name) == 0) { //linear regression
//    std::map<int, double> bars = this->get_desired_map(20);
//    auto res = this->auxiliary_linear_regression(bars);
//    double slope = std::get<0>(res);
//    //    std:: cout << "slope ==  " << slope;
//    double yintercept = std::get<1>(res);

//    //    std:: cout << "intercept ==  " << yintercept;
//    for (int k = 0; k < nb_points; k++) {
//      double image = slope * k + yintercept;
//      strategy_output.prepend(image);
//    }
//  }

  if (this->str2.compare(name) == 0) {
    return this->calculate_signals_mom();
  }


  if (this->str4.compare(name) == 0) {
    return this->calculate_signals_sma();
  }

  if (this->str3.compare(name) == 0) {
    return this->calculate_signals_lr();
  }


}


