#ifndef CADDLESSONINFO_H
#define CADDLESSONINFO_H

#include <QDialog>
#include <QDate>

namespace Ui {
class CAddLessonInfo;
}

class CAddLessonInfo : public QDialog
{
    Q_OBJECT

public:
    explicit CAddLessonInfo(QWidget *parent = nullptr);
    ~CAddLessonInfo();
    int m_lessonID;
    QString m_lessonName;
    QDateTime m_testDateTime;
    int m_testID;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CAddLessonInfo *ui;
};

#endif // CADDLESSONINFO_H
