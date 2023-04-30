#ifndef CADDCLASSINFODLG_H
#define CADDCLASSINFODLG_H

#include <QDialog>

namespace Ui {
class CAddClassInfoDlg;
}

class CAddClassInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CAddClassInfoDlg(QWidget *parent = nullptr);
    ~CAddClassInfoDlg();
    int m_classID;
    QString m_className;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CAddClassInfoDlg *ui;
};

#endif // CADDCLASSINFODLG_H
