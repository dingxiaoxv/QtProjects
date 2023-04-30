#ifndef ILOGIC_H
#define ILOGIC_H
#include "cstudentinfodto.h"
#include "cclassinfodto.h"
#include "clessoninfodto.h"
#include "cscoreinfodto.h"

class ILogic
{
public:
    ILogic();
    virtual ~ILogic();
    static ILogic* getInstance(QString connectString);
    virtual QList<CStudentInfoDTO> getStuInfo() = 0;
    virtual QList<CClassInfoDTO> getClassInfo() = 0;
    virtual QList<CStudentInfoDTO> getStuInfoByClass(QString className) = 0;
    virtual QList<CLessonInfoDTO> getLessonInfo() = 0;
    virtual QList<CScoreInfoDTO> getScoreInfo() = 0;
    virtual int addStuInfo(int studentID, QString studentName, int classID) = 0;
    virtual int deleteStuInfo(int stuID) = 0;
    virtual int editStuInfo(int studentID, QString studentName, int classID) = 0;
    virtual QList<CStudentInfoDTO> findStuInfo(int studentID) = 0;
    virtual int addClassInfo(int classID, QString className) = 0;
    virtual int deleteClassInfo(QString className) = 0;
    virtual int addLessonInfo(int lessonID, QString lessonName, int testID, QString testTime) = 0;
    virtual int addScoreInfo(int stuID, QString lessonName, int score) = 0;
    virtual int editScoreInfo(int stuID, QString lessonName, int score) = 0;
    virtual QString uploadStuInfo() = 0;
};

#endif // ILOGIC_H
