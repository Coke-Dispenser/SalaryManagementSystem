#ifndef UPDATEEMPLOYEEWINDOW_H
#define UPDATEEMPLOYEEWINDOW_H
#include "mainwindow.h"
#include <QDialog>
#include<QFileDialog>
#include <QPixmap>
#include <QPushButton>
#include <QMouseEvent>
#include<QLineEdit>


namespace Ui {
class updateEmployeewindow;
}

class updateEmployeewindow : public QDialog
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public:
    explicit updateEmployeewindow(MainWindow *mainWin,QWidget *parent = nullptr);
    ~updateEmployeewindow();
    QString getEffectiveText(QLineEdit *lineEdit);
signals:
    void UpdateEmployeeList();
private slots:
    void onCloseBtnClicked();
    void on_selectImageBtn_clicked();
    void on_confirmButton_clicked();

private:
    MainWindow *mainWindowptr;
    Ui::updateEmployeewindow *ui;
    QString imagePath="";
    bool dragging;          // 拖动状态标志
    QPoint dragPosition;    // 拖动位置记录
    void setplaceholderText();
};


#endif // UPDATEEMPLOYEEWINDOW_H
