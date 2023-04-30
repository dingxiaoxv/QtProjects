#ifndef CADDSCOREINFODLG_H
#define CADDSCOREINFODLG_H

#include <QDialog>

namespace Ui {
class CAddScoreInfoDlg;
}

class CAddScoreInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CAddScoreInfoDlg(QWidget *parent = nullptr);
    ~CAddScoreInfoDlg();
    int m_stuID;
    QString m_lessonName;
    int m_score;


private slots:
    void on_buttonBox_accepted();

private:
    Ui::CAddScoreInfoDlg *ui;
};

#endif // CADDSCOREINFODLG_H
