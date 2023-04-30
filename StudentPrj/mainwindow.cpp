#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "caddstuinfodlg.h"
#include "cfindstudlg.h"
#include "caddclassinfodlg.h"
#include "caddlessoninfo.h"
#include "caddscoreinfodlg.h"
#include "cstudentinfodto.h"
#include "cclassinfodto.h"
#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->stu_model = new QStandardItemModel(ui->tableView);
    this->stu_model->setHorizontalHeaderLabels(QStringList()<<"学号"<<"姓名"<<"班级名称");
    this->class_model = new QStandardItemModel(ui->treeView);
    ui->treeView->setModel(class_model);
    this->lesson_model = new QStandardItemModel(ui->tableView);
    lesson_model->setHorizontalHeaderLabels(QStringList()<<"课程号"<<"课程名"<<"考试时间");
    this->score_model = new QStandardItemModel(ui->tableView);
    score_model->setHorizontalHeaderLabels(QStringList()<<"学号"<<"姓名"<<"班级"<<"课程"<<"成绩");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//显示学生信息
void MainWindow::showStudentInfo(QList<CStudentInfoDTO> list)
{
    //将table_model放入容器中
    ui->tableView->setModel(stu_model);
    stu_model->removeRows(0,stu_model->rowCount());
    int rowIndex = 0;
    for(CStudentInfoDTO stu:list)
    {
        QStandardItem* a = new QStandardItem(QString("%1").arg(stu.getStuID()));
        stu_model->setItem(rowIndex,0,a);
        a->setCheckable(true);
        a->setEditable(false);
        QStandardItem* b = new QStandardItem(stu.getStuName());
        stu_model->setItem(rowIndex,1,b);
        QStandardItem* c = new QStandardItem(stu.getClassName());
        stu_model->setItem(rowIndex,2,c);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选中时为整行选中
        rowIndex++;
    }
}
//显示班级信息
void MainWindow::showClassInfo()
{ 
    class_model->removeRows(0,class_model->rowCount());
    QList<CClassInfoDTO> list = pLogic->getClassInfo();
    QStandardItem *parentItem = class_model->invisibleRootItem();
    QStandardItem *root = new QStandardItem("班级");
    parentItem->appendRow(root);
    for(CClassInfoDTO cla:list)
    {
        if(cla.getClassStatus() != 1)
        {
            QStandardItem* a = new QStandardItem(cla.getClassName());
            ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选中时为整行选中
            a->setCheckable(true);
            a->setEditable(false);
            root->appendRow(a);
        }
    }
}
//显示课程信息
void MainWindow::showLessonInfo()
{
    ui->tableView->setModel(lesson_model);
    QList<CLessonInfoDTO> list = pLogic->getLessonInfo();
    int rowIndex = 0;
    for(CLessonInfoDTO lesson:list)
    {
        QStandardItem* a = new QStandardItem(QString("%1").arg(lesson.getLessonID()));
        lesson_model->setItem(rowIndex,0,a);
        QStandardItem* b = new QStandardItem(lesson.getLessonName());
        lesson_model->setItem(rowIndex,1,b);
        QStandardItem* c = new QStandardItem(lesson.getTestTime());
        lesson_model->setItem(rowIndex,2,c);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选中时为整行选中
        rowIndex++;
    }
}
//显示分数信息
void MainWindow::showScoreInfo()
{
    ui->tableView->setModel(score_model);
    QList<CScoreInfoDTO> list = pLogic->getScoreInfo();
    int rowIndex = 0;
    for(CScoreInfoDTO stu:list)
    {
        QStandardItem* a = new QStandardItem(QString("%1").arg(stu.getStuID()));
        score_model->setItem(rowIndex,0,a);
        a->setCheckable(true);
        a->setEditable(false);
        QStandardItem* b = new QStandardItem(stu.getStuName());
        score_model->setItem(rowIndex,1,b);
        QStandardItem* c = new QStandardItem(stu.getClassName());
        score_model->setItem(rowIndex,2,c);
        QStandardItem* d = new QStandardItem(stu.getLessonName());
        score_model->setItem(rowIndex,3,d);
        QStandardItem* e = new QStandardItem(QString("%1").arg(stu.getScore()));
        score_model->setItem(rowIndex,4,e);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选中时为整行选中
        rowIndex++;
    }
}
//打开数据库
void MainWindow::on_action_OpenDataBase_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("文件对话框"),"D:", tr("所有文件(*.*)"));
    pLogic = ILogic::getInstance(fileName);
    //pLogic = ILogic::getInstance("D:/StudyFiles/SQL/test.db");
    showStudentInfo(pLogic->getStuInfo());
    showClassInfo();
}
//点击班级显示学生信息
void MainWindow::on_treeView_pressed(const QModelIndex &index)
{
    QString className = class_model->data(index, Qt::EditRole).toString();
    showStudentInfo(pLogic->getStuInfoByClass(className));
}
//添加学生信息
void MainWindow::on_action_AddStuInfo_triggered()
{
    CAddStuInfoDlg dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        if(!pLogic->addStuInfo(dlg.m_stuID,dlg.m_stuName,dlg.m_classID))
        {
            QMessageBox::critical(this,"错误","学生信息添加失败！");
        }
        showStudentInfo(pLogic->getStuInfo());
    }
}
//删除学生信息
void MainWindow::on_action_DeleteStuInfo_triggered()
{
    QList<int> list;
    for(int i=0;i<stu_model->rowCount();i++)
    {
        QStandardItem *pItem = stu_model->item(i,0);
        if(pItem->checkState()) //查看checkbox状态
        {
            QString ids = pItem->data(0).toString();
            list << ids.toInt();
            stu_model->removeRow(i);
            i--;
        }
    }
    for(int id:list)
    {
        if(!pLogic->deleteStuInfo(id))
        {
            QMessageBox::critical(this,"错误","学生信息删除失败！");
            break;
        }
    }
    showStudentInfo(pLogic->getStuInfo());
}
//修改学生信息
void MainWindow::on_action_EditStuInfo_triggered()
{
    for(int i=0;i<stu_model->rowCount();i++)
    {
        QStandardItem *pItem = stu_model->item(i,0);
        if(pItem->checkState()) //查看checkbox状态
        {
            int stuID = pItem->data(0).toInt();
            QString stuName = stu_model->item(i,1)->text();
            int classID = pItem->data(2).toInt();
            if(!pLogic->editStuInfo(stuID,stuName,classID))
            {
                QMessageBox::critical(this,"错误","学生信息修改失败！");
                break;
            }
        }
    }
    showStudentInfo(pLogic->getStuInfo());
}
//显示学生信息
void MainWindow::on_action_ShowStuInfo_triggered()
{
    showStudentInfo(pLogic->getStuInfo());
}
//查找学生信息
void MainWindow::on_action_FindStu_triggered()
{
    CFindStuDlg dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        showStudentInfo(pLogic->findStuInfo(dlg.m_stuID));
    }
}
//添加班级
void MainWindow::on_action_AddClass_triggered()
{
    CAddClassInfoDlg dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        if(!pLogic->addClassInfo(dlg.m_classID,dlg.m_className))
        {
            QMessageBox::critical(this,"错误","班级信息添加失败！");
        }
        showClassInfo();
    }
}
//删除班级
void MainWindow::on_action_DeleteClass_triggered()
{
    QList<QString> list;
    for(int i=0;i<class_model->rowCount();i++)
    {
        QStandardItem *pItem = class_model->item(i,0);
        if(pItem->hasChildren())
        {
            for(int j=0;j<pItem->rowCount();j++)
            {
                QStandardItem * childitem = pItem->child(j);
                if(childitem->checkState()) //查看checkbox状态
                {
                    QString classes = childitem->data(0).toString();
                    list.append(classes);
                }
            }
        }
    }
    for(QString str:list)
    {
        if(!pLogic->deleteClassInfo(str))
        {
            QMessageBox::critical(this,"错误","班级信息删除失败！");
            break;
        }
    }
    showClassInfo();
}
//添加课程
void MainWindow::on_action_AddLesson_triggered()
{
    CAddLessonInfo dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        if(!pLogic->addLessonInfo(dlg.m_lessonID,dlg.m_lessonName,dlg.m_testID,dlg.m_testDateTime.toString("yyyy-MM-dd HH:mm:ss")))
        {
            QMessageBox::critical(this,"错误","课程信息添加失败！");
        }
    }
    showLessonInfo();
}
//添加成绩
void MainWindow::on_action_AddScore_triggered()
{
    CAddScoreInfoDlg dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        if(!pLogic->addScoreInfo(dlg.m_stuID,dlg.m_lessonName,dlg.m_score))
        {
            QMessageBox::critical(this,"错误","成绩信息添加失败！");
        }
    }
    showScoreInfo();
}
//修改成绩
void MainWindow::on_action_EditScore_triggered()
{
    for(int i=0;i<score_model->rowCount();i++)
    {
        QStandardItem *pItem = score_model->item(i,0);
        if(pItem->checkState()) //查看checkbox状态
        {
            int stuID = pItem->data(0).toInt();
            QString lessonName = score_model->item(i,3)->text();
            int score = score_model->item(i,4)->text().toInt();
            if(!pLogic->editScoreInfo(stuID,lessonName,score))
            {
                QMessageBox::critical(this,"错误","成绩信息修改失败！");
                break;
            }
        }
    }
    showScoreInfo();
}
//显示学生信息
void MainWindow::on_action_ShowScore_triggered()
{
    showScoreInfo();
}
//上传学生信息
void MainWindow::on_action_updateStuInfo_triggered()
{
    QString res = pLogic->uploadStuInfo();
    QMessageBox::critical(this,"响应", res);
}

