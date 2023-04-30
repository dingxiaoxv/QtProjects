#include "caddstuinfodlg.h"
#include "ui_caddstuinfodlg.h"

CAddStuInfoDlg::CAddStuInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddStuInfoDlg)
{
    ui->setupUi(this);
}

CAddStuInfoDlg::~CAddStuInfoDlg()
{
    delete ui;
}

void CAddStuInfoDlg::on_buttonBox_accepted()
{
    m_stuID = ui->lineEdit_stuID->text().toInt();
    m_stuName = ui->lineEdit_stuName->text();
    m_classID = ui->lineEdit_classID->text().toInt();
}

