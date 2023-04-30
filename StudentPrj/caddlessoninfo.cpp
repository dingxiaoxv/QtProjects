#include "caddlessoninfo.h"
#include "ui_caddlessoninfo.h"

CAddLessonInfo::CAddLessonInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddLessonInfo)
{
    ui->setupUi(this);
}

CAddLessonInfo::~CAddLessonInfo()
{
    delete ui;
}

void CAddLessonInfo::on_buttonBox_accepted()
{
    m_lessonID = ui->lineEdit_LessonID->text().toInt();
    m_lessonName = ui->lineEdit_LessonName->text();
    m_testDateTime = ui->dateTimeEdit->dateTime();
    m_testID = ui->lineEdit_TestID->text().toInt();
}

