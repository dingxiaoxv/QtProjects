#include "cclassinfodto.h"

CClassInfoDTO::CClassInfoDTO()
{

}

CClassInfoDTO::CClassInfoDTO(int classID, QString className, int classStatus)
{
    this->classID = classID;
    this->className = className;
    this->classStatus = classStatus;
}

int CClassInfoDTO::getClassID()
{
    return classID;
}

void CClassInfoDTO::setClassID(int id)
{
    classID = id;
}

QString CClassInfoDTO::getClassName()
{
    return className;
}

void CClassInfoDTO::setClassName(QString name)
{
    className = name;
}

int CClassInfoDTO::getClassStatus()
{
    return classStatus;
}

void CClassInfoDTO::setClassStatus(int status)
{
    classStatus = status;
}
