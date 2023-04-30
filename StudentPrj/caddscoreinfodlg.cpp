#include "caddscoreinfodlg.h"
#include "ui_caddscoreinfodlg.h"

CAddScoreInfoDlg::CAddScoreInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddScoreInfoDlg)
{
    ui->setupUi(this);
}

CAddScoreInfoDlg::~CAddScoreInfoDlg()
{
    delete ui;
}

void CAddScoreInfoDlg::on_buttonBox_accepted()
{
    m_stuID = ui->lineEdit_stuID->text().toInt();
    m_score = ui->lineEdit_score->text().toInt();
    m_lessonName = ui->lineEdit_lessonName->text();
}

