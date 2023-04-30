#include "cstudentinfodto.h"

CStudentInfoDTO::CStudentInfoDTO()
{

}

CStudentInfoDTO::CStudentInfoDTO(int stuID, QString stuName, QString className)
{
    this->stuID = stuID;
    this->stuName = stuName;
    this->className = className;
}

int CStudentInfoDTO::getStuID()
{
    return stuID;
}

void CStudentInfoDTO::setStuID(int id)
{
    stuID = id;
}

QString CStudentInfoDTO::getStuName()
{
    return stuName;
}

void CStudentInfoDTO::setStuName(QString name)
{
    stuName = name;
}

QString CStudentInfoDTO::getClassName()
{
    return className;
}

void CStudentInfoDTO::setClassName(QString name)
{
    className = name;
}
