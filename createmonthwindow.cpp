#include "createMonthwindow.h"
#include "ui_createMonthwindow.h"
#include <qevent.h>

createMonthwindow::createMonthwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createMonthwindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeButton, &QPushButton::clicked, this, &createMonthwindow::onCloseBtnClicked);
}

createMonthwindow::~createMonthwindow()
{
    delete ui;
}
void createMonthwindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        // 记录鼠标相对于窗口的位置
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

// 实现窗口拖动
void createMonthwindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        // 移动窗口
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

// 结束拖动
void createMonthwindow::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}
void createMonthwindow::onCloseBtnClicked()
{
    close();  // 关闭窗口
}

void createMonthwindow::on_confirmButton_clicked()
{
    QString Monthtext=ui->lineEdit->text();
    Month* monthInstance = Month::getInstance();
    if(monthInstance->isMonthValid(Monthtext))
    {
        monthInstance->createMonth(Monthtext);
        emit MonthViewLabelChange(Monthtext);
        close();
    }
    else
    {
        ui->lineEdit->setStyleSheet("border: 2px solid red;");
        ui->warningLabel->setText("月份已存在");
           QTimer::singleShot(1000, this, [=]() {
            ui->lineEdit->setStyleSheet("border:1px solid rgb(90, 90, 90)");
            ui->warningLabel->setText("");
        });
        return;
    }
}

