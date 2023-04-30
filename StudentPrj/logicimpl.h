#ifndef LOGICIMPL_H
#define LOGICIMPL_H
#include <QSqlDatabase>
#include "ilogic.h"

class LogicImpl : public ILogic
{
public:
    LogicImpl();
    LogicImpl(QString connectString);
    ~LogicImpl();
    QList<CStudentInfoDTO> getStuInfo() override;
    QList<CClassInfoDTO> getClassInfo() override;
    QList<CStudentInfoDTO> getStuInfoByClass(QString className) override;
    QList<CLessonInfoDTO> getLessonInfo() override;
    QList<CScoreInfoDTO> getScoreInfo() override;
    int addStuInfo(int studentID, QString studentName, int classID) override;
    int deleteStuInfo(int stuID) override;
    int editStuInfo(int studentID, QString studentName, int classID) override;
    QList<CStudentInfoDTO> findStuInfo(int studentID) override;
    int addClassInfo(int classID, QString className) override;
    int deleteClassInfo(QString className) override;
    int addLessonInfo(int lessonID, QString lessonName, int testID, QString testTime) override;
    int addScoreInfo(int stuID, QString lessonName, int score) override;
    int editScoreInfo(int stuID, QString lessonName, int score) override;
    QString uploadStuInfo() override;
private:
    QSqlDatabase database; //数据库
    int findTestID(QString lessonName);
};

#endif // LOGICIMPL_H
