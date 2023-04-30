#ifndef CCLASSINFODTO_H
#define CCLASSINFODTO_H
#include <QString>

class CClassInfoDTO
{
public:
    CClassInfoDTO();
    CClassInfoDTO(int classID, QString className, int classStatus);
    int getClassID();
    void setClassID(int id);
    QString getClassName();
    void setClassName(QString name);
    int getClassStatus();
    void setClassStatus(int status);
private:
    int classID;
    QString className;
    int classStatus;
};

#endif // CCLASSINFODTO_H
