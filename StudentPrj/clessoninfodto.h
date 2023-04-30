#ifndef CLESSONINFODTO_H
#define CLESSONINFODTO_H
#include <QString>

class CLessonInfoDTO
{
public:
    CLessonInfoDTO();
    CLessonInfoDTO(int lessonID, QString lessonName, QString testTime);
    int getLessonID();
    void setLessonID(int id);
    QString getLessonName();
    void setLessonName(QString name);
    QString getTestTime();
    void setTestTime(QString time);

private:
    int lessonID;
    QString lessonName;
    QString testTime;
};

#endif // CLESSONINFODTO_H
