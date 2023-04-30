#ifndef CSCOREINFODTO_H
#define CSCOREINFODTO_H
#include <QString>

class CScoreInfoDTO
{
public:
    CScoreInfoDTO();
    CScoreInfoDTO(int stuID, QString stuName, QString className, QString lessonName, int score);
    int getStuID();
    void setStuID(int id);
    QString getStuName();
    void setStuName(QString name);
    QString getClassName();
    void setClassName(QString name);
    QString getLessonName();
    void setLessonName(QString name);
    int getScore();
    void setScore(int score);

private:
    int stuID;
    QString stuName;
    QString className;
    QString lessonName;
    int score;
};

#endif // CSCOREINFODTO_H
