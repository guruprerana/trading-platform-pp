#ifndef QENUMMANIPULATION_H
#define QENUMMANIPULATION_H

#include <QString>
#include <QMetaEnum>

template<typename QEnum>
QString QEnumToQString(const QEnum value) {
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

template <typename T>
T QStringToQEnum(const QString &s) {
  return static_cast<T>(QMetaEnum::fromType<T>().keyToValue(s.toLocal8Bit()));
}

#endif // QENUMMANIPULATION_H
