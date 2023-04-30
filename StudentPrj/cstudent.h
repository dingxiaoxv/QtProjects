#ifndef CSTUDENT_H
#define CSTUDENT_H

#include <QString>

class CStudent
{
public:
    CStudent();
    CStudent(int stuID,
             QString stuName,
             int stuScore);
    int stuID;
    QString stuName;
    int classID;
    QString ToJson();
    static CStudent FromJson(QString srcStr);
    static QList<CStudent> FromJsonToList(QString srcStr);
};

#endif // CSTUDENT_H
