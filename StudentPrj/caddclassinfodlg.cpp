#include "caddclassinfodlg.h"
#include "ui_caddclassinfodlg.h"

CAddClassInfoDlg::CAddClassInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddClassInfoDlg)
{
    ui->setupUi(this);
}

CAddClassInfoDlg::~CAddClassInfoDlg()
{
    delete ui;
}

void CAddClassInfoDlg::on_buttonBox_accepted()
{
    m_classID = ui->lineEdit_ClassID->text().toInt();
    m_className = ui->lineEdit_ClassName->text();
}

