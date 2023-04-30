#include "cfindstudlg.h"
#include "ui_cfindstudlg.h"

CFindStuDlg::CFindStuDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CFindStuDlg)
{
    ui->setupUi(this);
}

CFindStuDlg::~CFindStuDlg()
{
    delete ui;
}

void CFindStuDlg::on_buttonBox_accepted()
{
    m_stuID = ui->lineEdit->text().toInt();
}

