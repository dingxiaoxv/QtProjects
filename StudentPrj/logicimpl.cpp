#include "logicimpl.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include "cstudent.h"

LogicImpl::LogicImpl()
{

}

LogicImpl::LogicImpl(QString connectString)
{
    database = QSqlDatabase::addDatabase("QSQLITE");// 启用数据库引擎
    database.setDatabaseName(connectString);
}

LogicImpl::~LogicImpl()
{

}

QList<CStudentInfoDTO> LogicImpl::getStuInfo()
{
    database.open();
    QString select_all_sql = "select studentid,studentname,classname from StudentInfoTable,ClassInfoTable where StudentInfoTable.ClassID=ClassInfoTable.ClassID order by studentid";
    QSqlQuery sql_query(database);
    sql_query.prepare(select_all_sql);
    sql_query.exec();
    QList<CStudentInfoDTO> list;
    while(sql_query.next())
    {
        int stuID = sql_query.value(0).toInt();
        QString stuName = sql_query.value(1).toString();
        QString className = sql_query.value(2).toString();
        CStudentInfoDTO stu(stuID,stuName,className);
        list.append(stu);
    }
    database.close();
    return list;
}

QList<CClassInfoDTO> LogicImpl::getClassInfo()
{
    database.open();
    QString select_all_sql = "select * from ClassInfoTable";
    QSqlQuery sql_query(database);
    sql_query.prepare(select_all_sql);
    sql_query.exec();
    QList<CClassInfoDTO> list;
    while(sql_query.next())
    {
        int classID = sql_query.value(0).toInt();
        QString className = sql_query.value(1).toString();
        int classStatus = sql_query.value(2).toInt();
        CClassInfoDTO cla(classID,className,classStatus);
        list.append(cla);
    }
    database.close();
    return list;
}

QList<CStudentInfoDTO> LogicImpl::getStuInfoByClass(QString className)
{
    database.open();
    QString select_class_sql = "select studentid,studentname,classname from StudentInfoTable, ClassInfoTable where StudentInfoTable.ClassID=ClassInfoTable.ClassID and classname=?";
    QSqlQuery sql_query(database);
    sql_query.prepare(select_class_sql);
    sql_query.addBindValue(className);
    sql_query.exec();
    QList<CStudentInfoDTO> list;
    while(sql_query.next())
    {
        int stuID = sql_query.value(0).toInt();
        QString stuName = sql_query.value(1).toString();
        QString className = sql_query.value(2).toString();
        CStudentInfoDTO stu(stuID,stuName,className);
        list.append(stu);
    }
    database.close();
    return list;
}

QList<CLessonInfoDTO> LogicImpl::getLessonInfo()
{
    database.open();
    QString select_all_sql = "select * from lessonView";
    QSqlQuery sql_query(database);
    sql_query.prepare(select_all_sql);
    sql_query.exec();
    QList<CLessonInfoDTO> list;
    while(sql_query.next())
    {
        int lessonID = sql_query.value(0).toInt();
        QString lessonName = sql_query.value(1).toString();
        QString testTime = sql_query.value(2).toString();
        CLessonInfoDTO lesson(lessonID,lessonName,testTime);
        list.append(lesson);
    }
    database.close();
    return list;
}

QList<CScoreInfoDTO> LogicImpl::getScoreInfo()
{
    database.open();
    QString select_sql = "select * from scoreView";
    QSqlQuery sql_query(database);
    sql_query.prepare(select_sql);
    sql_query.exec();
    QList<CScoreInfoDTO> list;
    while(sql_query.next())
    {
        int stuID = sql_query.value(0).toInt();
        QString stuName = sql_query.value(1).toString();
        QString className = sql_query.value(2).toString();
        QString lessonName = sql_query.value(3).toString();
        int score = sql_query.value(4).toInt();
        CScoreInfoDTO stu(stuID,stuName,className,lessonName,score);
        list.append(stu);
    }
    database.close();
    return list;
}

int LogicImpl::addStuInfo(int studentid, QString studentname, int classid)
{
    database.open();
    QString insert_sql = "insert into StudentInfoTable(studentid,studentname,classid) values(?,?,?)";
    QSqlQuery sql_query(database);
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(studentid);
    sql_query.addBindValue(studentname);
    sql_query.addBindValue(classid);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    else
    {
        database.close();
        return 1;
    }
}

int LogicImpl::deleteStuInfo(int stuID)
{
    database.open();
    QString delete_sql = "delete from StudentInfoTable where StudentID=?";
    QSqlQuery sql_query(database);
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(stuID);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    else
    {
        database.close();
        return 1;
    }
}

int LogicImpl::editStuInfo(int studentID, QString studentName, int classID)
{
    database.open();
    QString update_sql = "update StudentInfoTable set studentname=?,classid=? where studentid=?";
    QSqlQuery sql_query(database);
    sql_query.prepare(update_sql);
    sql_query.addBindValue(studentName);
    sql_query.addBindValue(classID);
    sql_query.addBindValue(studentID);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    else
    {
        database.close();
        return 1;
    }
}

QList<CStudentInfoDTO> LogicImpl::findStuInfo(int studentID)
{
    database.open();
    QString find_sql = "select * from StudentInfoTable where studentid=?";
    QSqlQuery sql_query(database);
    sql_query.prepare(find_sql);
    sql_query.addBindValue(studentID);
    sql_query.exec();
    QList<CStudentInfoDTO> list;
    while(sql_query.next())
    {
        int stuID = sql_query.value(0).toInt();
        QString stuName = sql_query.value(1).toString();
        QString className = sql_query.value(2).toString();
        CStudentInfoDTO stu(stuID,stuName,className);
        list.append(stu);
    }
    database.close();
    return list;
}

int LogicImpl::addClassInfo(int classID, QString className)
{
    database.open();
    QString insert_sql = "insert into ClassInfoTable(classid,classname) values(?,?)";
    QSqlQuery sql_query(database);
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(classID);
    sql_query.addBindValue(className);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    else
    {
        database.close();
        return 1;
    }
}

int LogicImpl::deleteClassInfo(QString className)
{
    database.open();
    QString update_sql = "update ClassInfoTable set classstatus=1 where classname=?";
    QSqlQuery sql_query(database);
    sql_query.prepare(update_sql);
    sql_query.addBindValue(className);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    else
    {
        database.close();
        return 1;
    }
}

int LogicImpl::addLessonInfo(int lessonID, QString lessonName, int testID, QString testTime)
{
    database.open();
    QString insert_sql = "insert into LessonInfoTable(lessonid,lessonname) values(?,?)";
    QSqlQuery sql_query(database);
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(lessonID);
    sql_query.addBindValue(lessonName);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    insert_sql = "insert into TestInfoTable(testid,lessonid,testtime) values(?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(testID);
    sql_query.addBindValue(lessonID);
    sql_query.addBindValue(testTime);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    database.close();
    return 1;
}

int LogicImpl::findTestID(QString lessonName)
{
    QString find_sql = "select testid from TestInfoTable,LessonInfoTable where TestInfoTable.LessonID=LessonInfoTable.LessonID and lessonname=?";
    QSqlQuery sql_query(database);
    sql_query.prepare(find_sql);
    sql_query.addBindValue(lessonName);
    if(!sql_query.exec())
    {
        return 0;
    }
    int testID = 0;
    while(sql_query.next())
    {
        testID = sql_query.value(0).toInt();
    }
    return testID;
}

int LogicImpl::addScoreInfo(int stuID, QString lessonName, int score)
{
    database.open();
    QString insert_sql = "insert into ScoreInfoTable(StudentID,TestID,Score) values(?,?,?)";
    QSqlQuery sql_query(database);
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(stuID);
    sql_query.addBindValue(findTestID(lessonName));
    sql_query.addBindValue(score);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    else
    {
        database.close();
        return 1;
    }
}

int LogicImpl::editScoreInfo(int stuID, QString lessonName, int score)
{
    database.open();
    QString update_sql = "update ScoreInfoTable set score=? where studentid=? and testid=?";
    QSqlQuery sql_query(database);
    sql_query.prepare(update_sql);
    sql_query.addBindValue(score);
    sql_query.addBindValue(stuID);
    int testID = findTestID(lessonName);
    sql_query.addBindValue(testID);
    if(!sql_query.exec())
    {
        database.close();
        return 0;
    }
    else
    {
        database.close();
        return 1;
    }
}

QString LogicImpl::uploadStuInfo()
{
    database.open();
    QString select_all_sql = "select * from StudentInfoTable order by studentid";
    QSqlQuery sql_query(database);
    sql_query.prepare(select_all_sql);
    sql_query.exec();
    QList<CStudent> list;
    while(sql_query.next())
    {
        int stuID = sql_query.value(0).toInt();
        QString stuName = sql_query.value(1).toString();
        int classID = sql_query.value(2).toInt();
        CStudent stu(stuID,stuName,classID);
        list.append(stu);
    }
    database.close();
    QString jsonStr="[";
    for(auto val:list)
    {
        QString stuStr = val.ToJson();
        jsonStr = jsonStr+stuStr + ",";
    }
    jsonStr[jsonStr.length()-1]=']'; //替换多余","
    //qDebug()<<jsonStr;
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest req;
    req.setUrl(QUrl("http://localhost:8080/JsonWeb/JsonLet"));
    //通过网络提交http请求到服务端 ，异步方法发送post请求
    manager->post(req,jsonStr.toUtf8());
    //响应
    QString response;
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     [&](QNetworkReply* reply){
        if(reply->error() != QNetworkReply::NoError)
        {
            response = reply->errorString();
        }
        QByteArray buf = reply->readAll();
        QString srcStr(buf);
        response = srcStr;
    });
    delete manager;
    return response;
}

