#ifndef DELETEEMPLOYEEWINDOW_H
#define DELETEEMPLOYEEWINDOW_H

#include <QDialog>
#include <QWidget>
#include<QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include"mainwindow.h"


namespace Ui {
class deleteEmployeewindow;
}

class deleteEmployeewindow : public QDialog
{
    Q_OBJECT
signals:
    void UpdateEmployeeList();
public:
    explicit deleteEmployeewindow(MainWindow *mainWin,QWidget *parent = nullptr);
    ~deleteEmployeewindow();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:

    void onCloseBtnClicked();// 右上关闭按钮点击事件
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    MainWindow *mainWindowptr;
    Ui::deleteEmployeewindow *ui;
    bool dragging;          // 拖动状态标志
    QPoint dragPosition;    // 拖动位置记录
};

#endif // DELETEEMPLOYEEWINDOW_H
