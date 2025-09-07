#ifndef FINDEMPLOYEEWINDOW_H
#define FINDEMPLOYEEWINDOW_H

#include <QDialog>
#include <QWidget>
#include<QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include "mainwindow.h"

namespace Ui {
class findEmployeewindow;
}

class findEmployeewindow : public QDialog
{
    Q_OBJECT

public:
    explicit findEmployeewindow(MainWindow *mainWin,QWidget *parent = nullptr);
    ~findEmployeewindow();
signals:
    void UpdateEmployeeList();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:

    void onCloseBtnClicked();// 右上关闭按钮点击事件
    void on_confirmButton_clicked();
private:
    MainWindow *mainWindowptr;
    Ui::findEmployeewindow *ui;
    bool dragging;          // 拖动状态标志
    QPoint dragPosition;    // 拖动位置记录
};

#endif // FINDEMPLOYEEWINDOW_H
