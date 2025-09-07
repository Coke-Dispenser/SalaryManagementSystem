#ifndef ADDEMPLOYEEWINDOW_H
#define ADDEMPLOYEEWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QFileDialog>
#include <QPushButton>
#include <QMouseEvent>
#include<QWidget>
#include<QTimer>
#include "mainwindow.h"

namespace Ui {
class addEmployeewindow;
}

class addEmployeewindow : public QDialog
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public:
    explicit addEmployeewindow(MainWindow *mainWin, QWidget *parent = nullptr);
    ~addEmployeewindow();
signals:
    void UpdateEmployeeList();
private slots:
    void onCloseBtnClicked();
    void on_selectImageBtn_clicked();
    void on_confirmButton_clicked();

private:
    MainWindow *mainWindowptr;
    Ui::addEmployeewindow *ui;
    QString imagePath=":/image/image/default.png";
    bool dragging;          // 拖动状态标志
    QPoint dragPosition;    // 拖动位置记录
};

#endif // ADDEMPLOYEEWINDOW_H
