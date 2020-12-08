#ifndef QJSONOBJECTMANIPULATION_H
#define QJSONOBJECTMANIPULATION_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <chrono>

//converts string to QJsonObject
inline QJsonObject parseJson(std::string apiResponse) {
  QString QapiResponse = QString::fromStdString(apiResponse);
  QJsonDocument doc = QJsonDocument::fromJson(QapiResponse.toUtf8());
  QJsonObject jsonData = doc.object();
  return jsonData;
}


//converts QJsonObject to string
inline std::string convertToJson(QJsonObject jsonData) {
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

#endif // QJSONOBJECTMANIPULATION_H
