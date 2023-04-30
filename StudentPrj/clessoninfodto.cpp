#include "clessoninfodto.h"

CLessonInfoDTO::CLessonInfoDTO()
{

}

CLessonInfoDTO::CLessonInfoDTO(int lessonID, QString lessonName, QString testTime)
{
    this->lessonID = lessonID;
    this->lessonName = lessonName;
    this->testTime = testTime;
}

int CLessonInfoDTO::getLessonID()
{
    return lessonID;
}

void CLessonInfoDTO::setLessonID(int id)
{
    lessonID = id;
}

QString CLessonInfoDTO::getLessonName()
{
    return lessonName;
}

void CLessonInfoDTO::setLessonName(QString name)
{
    lessonName = name;
}

QString CLessonInfoDTO::getTestTime()
{
    return testTime;
}

void CLessonInfoDTO::setTestTime(QString time)
{
    testTime = time;
}
