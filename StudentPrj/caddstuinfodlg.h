#ifndef CADDSTUINFODLG_H
#define CADDSTUINFODLG_H

#include <QDialog>

namespace Ui {
class CAddStuInfoDlg;
}

class CAddStuInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CAddStuInfoDlg(QWidget *parent = nullptr);
    ~CAddStuInfoDlg();
    int m_stuID;
    QString m_stuName;
    int m_classID;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CAddStuInfoDlg *ui;
};

#endif // CADDSTUINFODLG_H
