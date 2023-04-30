#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardItemModel>
#include "ilogic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel *stu_model;
    QStandardItemModel *lesson_model;
    QStandardItemModel *score_model;
    QStandardItemModel *class_model;
    ILogic* pLogic;
    int m_lessonCount = 0;

    void updateTable(QSqlQuery &sql_query);
    void showStudentInfo(QList<CStudentInfoDTO> list);
    void showClassInfo();
    void showLessonInfo();
    void showScoreInfo();

private slots:
    void on_action_OpenDataBase_triggered();
    void on_treeView_pressed(const QModelIndex &index);
    void on_action_AddStuInfo_triggered();
    void on_action_DeleteStuInfo_triggered();
    void on_action_EditStuInfo_triggered();
    void on_action_ShowStuInfo_triggered();
    void on_action_FindStu_triggered();
    void on_action_AddClass_triggered();
    void on_action_DeleteClass_triggered();
    void on_action_AddLesson_triggered();
    void on_action_AddScore_triggered();
    void on_action_ShowScore_triggered();
    void on_action_EditScore_triggered();
    void on_action_updateStuInfo_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
