#ifndef CFINDSTUDLG_H
#define CFINDSTUDLG_H

#include <QDialog>

namespace Ui {
class CFindStuDlg;
}

class CFindStuDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CFindStuDlg(QWidget *parent = nullptr);
    ~CFindStuDlg();
    int m_stuID;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CFindStuDlg *ui;
};

#endif // CFINDSTUDLG_H
