#include "helper.h"
#include <iostream>

// Converts string to QJsonObject
QJsonObject helper::parseJson(std::string apiResponse) {
  QString QapiResponse = QString::fromStdString(apiResponse);
  QJsonDocument doc = QJsonDocument::fromJson(QapiResponse.toUtf8());
  QJsonObject jsonData = doc.object();
  return jsonData;
}

// Converts QJsonObject to string
std::string helper::convertToString(QJsonObject jsonData) {
  QJsonDocument doc(jsonData);
  QString strJson(doc.toJson(QJsonDocument::Compact));
  std::string textData = strJson.toUtf8().constData();
  return textData;
}

// Converts QString to std::string
std::string helper::toStdString(QString qs) {
  return qs.toUtf8().constData();
}

// Converts std::string to QString
QString helper::toQString(std::string s) {
  return QString::fromStdString(s);
}

// Converts unix timestamp to human-readable in YYYY-MM-DD format (the rest of seconds is neglected)
//  needed to call the api about market news. Will be called in api.h
std::string helper::convertToReadable(qint64 unixTimeStamp) {
  QString date =
    QDateTime::fromSecsSinceEpoch(unixTimeStamp).toString("yyyy-MM-dd");

  return toStdString(date);
}

//converts unix timestamp to human-readable in YYYY-MM-DD HH:MM format (the rest of seconds is neglected)
//needed to call the api about market news. Will be called in api.h
std::string helper::convertToFullTimeReadable(qint64 unixTimeStamp) {
  QString fullDate =
    QDateTime::fromSecsSinceEpoch(unixTimeStamp).toString("yyyy-MM-dd HH:MM");

  return toStdString(fullDate);
}

// Returns current Unix timestamp time.
qint64 helper::getCurrentTime() {
  return QDateTime::currentSecsSinceEpoch();
}

// Returns the current day in the format yyyy-MM-DD
std::string helper::getCurrentDate() {
  QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
  return toStdString(currentDate);
}

// Returns the current day in the format YYYY-MM-DD HH:mm
std::string helper::getCurrentFullDate() {
  QString currentFullDate =
    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
  return toStdString(currentFullDate);
}

//converts QJsonValue to std::string
std::string helper::convertQJValueToStdString(QJsonValue value) {
  return value.toString().toUtf8().constData();
}

//converts the QJsonObject that we have to a std::map<std::string, std::map<long, double>>
std::map<std::string, std::map<long, double>> helper::convertToMap(
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

// converts std::string to QJsonArray
QJsonArray helper::convertStringToQJsonArray(std::string apiResponse) {
  QJsonArray jsonArray;
  std::string cur = "";
  bool open = true;

  for (auto &c : apiResponse) {
    if (c == '[' || c == ']') {
      continue;
    }

    if (c == ',' && !open) {
      open = true;

      if (!cur.empty()) {
        jsonArray.append(parseJson(cur));
        cur = "";
      }
    }

    else {
      cur += c;
    }

    if (c == '}') {
      open = false;
    }
  }

  if (!cur.empty()) {
    jsonArray.append(parseJson(cur));
  }

  return jsonArray;
}

QVector<double> helper::convert_to_vector(QJsonObject j, std::string k) {
//  qDebug() << j << endl;
  QVariantMap j_map = j.toVariantMap();
  QVariantList j_list = j_map[k.c_str()].toList();
  QVector<double> q;

  for (int i = 0; i < j_list.count(); i++) {
    q.append(j_list[i].toDouble());
  }

  return q;
}
