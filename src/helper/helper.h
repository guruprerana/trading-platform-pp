#ifndef HELPER_H
#define HELPER_h

#include <QDateTime>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMetaEnum>
#include <chrono>
#include <map>
#include <QVector>

namespace helper {
QJsonObject parseJson(std::string apiResponse);
std::string convertToString(QJsonObject jsonData);
std::string toStdString(QString qs);
QString toQString(std::string s);
std::string convertToReadable(qint64 unixTimeStamp);
std::string convertToFullTimeReadable(qint64 unixTimeStamp);
std::string convertQJValueToStdString(QJsonValue value);
std::map<std::string, std::map<long, double>> convertToMap(QJsonObject data);
QJsonArray convertStringToQJsonArray(std::string apiResponse);
qint64 getCurrentTime();
std::string getCurrentDate();
std::string getCurrentFullDate();
QVector<double> convert_to_vector(QJsonObject j, std::string k);

template<typename QEnum>
QString QEnumToQString(const QEnum value) {
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

template <typename T>
T QStringToQEnum(const QString &s) {
  return static_cast<T>(QMetaEnum::fromType<T>().keyToValue(s.toLocal8Bit()));
}

}



#endif // HELPER_H
