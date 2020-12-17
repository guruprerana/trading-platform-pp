#ifndef QJSONOBJECTMANIPULATION_H
#define QJSONOBJECTMANIPULATION_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <chrono>
#include <map>

//converts string to QJsonObject
inline QJsonObject parseJson(std::string apiResponse) {
  QString QapiResponse = QString::fromStdString(apiResponse);
  QJsonDocument doc = QJsonDocument::fromJson(QapiResponse.toUtf8());
  QJsonObject jsonData = doc.object();
  return jsonData;
}


//converts QJsonObject to string
inline std::string convertToString(QJsonObject jsonData) {
  QJsonDocument doc(jsonData);
  QString strJson(doc.toJson(QJsonDocument::Compact));
  std::string textData = strJson.toUtf8().constData();
  return textData;
}

//converts unix timestamp to human-readable in YYYY-MM-DD format (the rest of seconds is neglected)
//needed to call the api about market news. Will be called in api.h
inline std::string convertToReadable(long unixTimeStamp) {
  std::tm *t = std::localtime(&unixTimeStamp);
  std::string date = std::to_string(t->tm_year + 1900);
  date += "-";

  if (t->tm_mon + 1 < 10) {
    date += "0";
  }

  date += std::to_string(t->tm_mon + 1);
  date += "-";

  if (t->tm_mday < 10) {
    date += "0";
  }

  date += std::to_string(t->tm_mday);
  return date;
}

//converts QJsonValue to std::string
inline std::string convertQJValueToStdString(QJsonValue value) {
  return value.toString().toUtf8().constData();
}

//converts the QJsonObject that we have to a std::map<std::string, std::map<long, double>>
inline std::map<std::string, std::map<long, double>> convertToMap(
QJsonObject data) {
  std::map<std::string, std::map<long, double>> res;
  std::map<long, double> mappingTimeToValue;
  QJsonObject::iterator i;

  QJsonArray timeStamp = data["t"].toArray();
  data.remove("t");
  data.remove("s");

  for (i = data.begin(); i != data.end(); ++i) {
    QJsonValue key = i.key();
    QJsonValue value = i.value();
    std::string k = convertQJValueToStdString(key);
    QJsonArray arr = value.toArray();

    for (int k = 0; k < timeStamp.count(); k ++) {
      mappingTimeToValue.insert({timeStamp[k].toInt(), arr[k].toDouble()});
    }

    res.insert({k, mappingTimeToValue});
    mappingTimeToValue.clear();
  }

  return res;
}
#endif
