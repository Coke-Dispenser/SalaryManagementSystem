#ifndef OUTPUTSALARYWINDOW_H
#define OUTPUTSALARYWINDOW_H

#include <QDialog>
#include <QDialog>
#include <QWidget>
#include<QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include"mainwindow.h"

namespace Ui {
class outputSalarywindow;
}

class outputSalarywindow : public QDialog
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:

    void onCloseBtnClicked();// 右上关闭按钮点击事件
    void on_outputEmployeeSalary_clicked();

    void on_outputMonthSalary_clicked();

public:
    explicit outputSalarywindow(MainWindow *mainWin,QWidget *parent = nullptr);
    ~outputSalarywindow();

private:
    Ui::outputSalarywindow *ui;
    MainWindow *mainWindowptr;
    bool dragging;          // 拖动状态标志
    QPoint dragPosition;    // 拖动位置记录

};

#endif // OUTPUTSALARYWINDOW_H
