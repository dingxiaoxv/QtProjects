#include "ilogic.h"
#include "logicimpl.h"

ILogic::ILogic()
{

}

ILogic::~ILogic()
{

}

ILogic *ILogic::getInstance(QString connectString)
{
    ILogic *p = new LogicImpl(connectString);
    return p;
}
