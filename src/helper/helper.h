#ifndef HELPER_H
#define HELPER_h

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <chrono>
#include <map>

namespace helper {
QJsonObject parseJson(std::string apiResponse);
std::string convertToString(QJsonObject jsonData);
std::string convertToReadable(long unixTimeStamp);
std::string convertQJValueToStdString(QJsonValue value);
std::map<std::string, std::map<long, double>> convertToMap(QJsonObject data);
QJsonArray convertStringToQJsonArray(std::string apiResponse);
}



#endif // HELPER_H
