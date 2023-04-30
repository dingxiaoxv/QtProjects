#include "cstudent.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CStudent::CStudent()
{

}

CStudent::CStudent(int stuID,
                   QString stuName,
                   int classID)
{
    this->stuID=stuID;
    this->stuName=stuName;
    this->classID=classID;
}

QString CStudent::ToJson()
{
    QJsonObject json;
    json.insert("stuID", this->stuID);
    json.insert("stuName", this->stuName);
    json.insert("classID", this->classID);
    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    return strJson;
}

CStudent CStudent::FromJson(QString srcStr)
{
    CStudent st;
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(srcStr.toUtf8(), &jsonError);  // 转化为 JSON 文档

    QJsonObject object = doucment.object();  // 转化为对象
    QJsonValue stuIDvalue = object.value("stuID");  // 获取指定 key 对应的 value
    QJsonValue stuNamevalue = object.value("stuName");  // 获取指定 key 对应的 value
    QJsonValue stuScorevalue = object.value("classID");  // 获取指定 key 对应的 value
    st.stuID = stuIDvalue.toInt();
    st.stuName = stuNamevalue.toString();
    st.classID = stuScorevalue.toInt();
    return st;
}

QList<CStudent> CStudent::FromJsonToList(QString srcStr)
{
    QList<CStudent> list;
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(srcStr.toUtf8(), &jsonError);  // 转化为 JSON 文档
    QJsonArray subArray = doucment.array();
    for(int i=0;i<subArray.count();i++)
    {
        QJsonValue StudentJson =subArray.at(i);
        QJsonObject object= StudentJson.toObject();
        int stuID = object.value("stuID").toInt();
        QString stuName = object.value("stuName").toString();
        int classID = object.value("classID").toDouble();
        CStudent st(stuID,stuName,classID);
        list.append(st);
    }
    return list;
}
