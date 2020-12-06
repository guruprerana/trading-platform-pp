#ifndef QJSONOBJECTMANIPULATION_H
#define QJSONOBJECTMANIPULATION_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

inline QJsonObject parseJson(std::string apiResponse){
    QString QapiResponse = QString::fromStdString(apiResponse);
    QJsonDocument doc = QJsonDocument::fromJson(QapiResponse.toUtf8());
    QJsonObject jsonData = doc.object();
    return jsonData;
}

inline std::string convertToJson(QJsonObject jsonData){
    QJsonDocument doc(jsonData);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    std::string textData = strJson.toUtf8().constData();
    return textData;
}

#endif // QJSONOBJECTMANIPULATION_H
