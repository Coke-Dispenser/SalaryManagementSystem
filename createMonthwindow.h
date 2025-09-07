#ifndef CREATEMONTHWINDOW_H
#define CREATEMONTHWINDOW_H

#include <QDialog>
#include <QWidget>
#include<QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include"Month.h"
namespace Ui {
class createMonthwindow;
}

class createMonthwindow : public QDialog
{
    Q_OBJECT
signals:
    void MonthViewLabelChange(const QString& month);
public:
    explicit createMonthwindow(QWidget *parent = nullptr);
    ~createMonthwindow();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:

    void onCloseBtnClicked();// 右上关闭按钮点击事件
    void on_confirmButton_clicked();

private:
    Ui::createMonthwindow *ui;
    bool dragging;          // 拖动状态标志
    QPoint dragPosition;    // 拖动位置记录

};

#endif // CREATEMONTHWINDOW_H
