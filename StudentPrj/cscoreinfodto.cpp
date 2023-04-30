#include "cscoreinfodto.h"

CScoreInfoDTO::CScoreInfoDTO()
{

}

CScoreInfoDTO::CScoreInfoDTO(int stuID, QString stuName, QString className, QString lessonName, int score)
{
    this->stuID = stuID;
    this->stuName = stuName;
    this->className = className;
    this->lessonName = lessonName;
    this->score = score;
}

int CScoreInfoDTO::getStuID()
{
    return stuID;
}

void CScoreInfoDTO::setStuID(int id)
{
    stuID = id;
}

QString CScoreInfoDTO::getStuName()
{
    return stuName;
}

void CScoreInfoDTO::setStuName(QString name)
{
    stuName = name;
}

QString CScoreInfoDTO::getClassName()
{
    return className;
}

void CScoreInfoDTO::setClassName(QString name)
{
    className = name;
}

QString CScoreInfoDTO::getLessonName()
{
    return lessonName;
}

void CScoreInfoDTO::setLessonName(QString name)
{
    lessonName = name;
}

int CScoreInfoDTO::getScore()
{
    return score;
}

void CScoreInfoDTO::setScore(int score)
{
    this->score = score;
}

