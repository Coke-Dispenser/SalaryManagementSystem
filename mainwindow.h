#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include"SalaryManagenment.h"
#include <QListView>
#include<QPixmap>
#include<QTimer>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getMonthLabelText() const;
    Employee* getSelectedEmployee();
    void setSelectedEmployee(Employee*emp);
    void changenlabel();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void SetListView();
    void setInfoView();


private slots:
    void updateMonthViewLabel(const QString& month);//更新月份显示标签
    void onCloseBtnClicked();//点击主窗口右上关闭按钮
    void on_createMonthButton_clicked();//点击月份创建按钮
    void on_addEmployeeButton_clicked();
    void on_EmployeeListView_clicked(const QModelIndex &index);
    void on_loadDataByMonthButton_clicked();
    void on_saveDataByMonthButton_clicked();
    void on_updateEmployeeButton_clicked();
    void on_deleteEmployeeButton_clicked();
    void on_getEmployeeButton_clicked();

private:
    Employee*SelectedEmployee=nullptr;
    Ui::MainWindow *ui;
    bool dragging;          // 拖动状态标志
    QPoint dragPosition;    // 拖动位置记录

};
#endif // MAINWINDOW_H
