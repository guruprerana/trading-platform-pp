#include "helper.h"

//converts string to QJsonObject
QJsonObject helper::parseJson(std::string apiResponse) {
  QString QapiResponse = QString::fromStdString(apiResponse);
  QJsonDocument doc = QJsonDocument::fromJson(QapiResponse.toUtf8());
  QJsonObject jsonData = doc.object();
  return jsonData;
}


//converts QJsonObject to string
std::string helper::convertToString(QJsonObject jsonData) {
  QJsonDocument doc(jsonData);
  QString strJson(doc.toJson(QJsonDocument::Compact));
  std::string textData = strJson.toUtf8().constData();
  return textData;
}

//converts unix timestamp to human-readable in YYYY-MM-DD format (the rest of seconds is neglected)
//needed to call the api about market news. Will be called in api.h
std::string helper::convertToReadable(long unixTimeStamp) {
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

//converts unix timestamp to human-readable in YYYY-MM-DD HH:MM format (the rest of seconds is neglected)
//needed to call the api about market news. Will be called in api.h
std::string helper::convertToFullTimeReadable(long unixTimeStamp) {
  std::tm *t = std::localtime(&unixTimeStamp);
  std::string fullDate = "";
  std::string basicDate = helper::convertToReadable(unixTimeStamp);
  std::string strHour = std::to_string(t->tm_hour);

  while (strHour.size() < 2) {
    strHour = '0' + strHour;
  }

  std::string strMin = std::to_string(t->tm_min);

  while (strMin.size() < 2) {
    strMin = '0' + strMin;
  }

  fullDate += basicDate + " " + strHour + ":" + strMin;
  return fullDate;

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
