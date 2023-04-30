#ifndef CSTUDENTINFODTO_H
#define CSTUDENTINFODTO_H
#include <QString>

class CStudentInfoDTO
{
public:
    CStudentInfoDTO();
    CStudentInfoDTO(int stuID, QString stuName, QString className);
    int getStuID();
    void setStuID(int id);
    QString getStuName();
    void setStuName(QString name);
    QString getClassName();
    void setClassName(QString name);
private:
    int stuID;
    QString stuName;
    QString className;
};

#endif // CSTUDENTINFODTO_H
