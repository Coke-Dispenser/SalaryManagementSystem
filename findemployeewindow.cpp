#include "findemployeewindow.h"
#include "ui_findemployeewindow.h"

findEmployeewindow::findEmployeewindow(MainWindow *mainWin,QWidget *parent)
    : QDialog(parent),mainWindowptr(mainWin)
    , ui(new Ui::findEmployeewindow)
{
    ui->setupUi(this);
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeButton, &QPushButton::clicked, this, &findEmployeewindow::onCloseBtnClicked);
    connect(ui->confirmButton,&QPushButton::clicked,this,&findEmployeewindow::on_confirmButton_clicked);
}

findEmployeewindow::~findEmployeewindow()
{
    delete ui;
}
void findEmployeewindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        // 记录鼠标相对于窗口的位置
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

// 实现窗口拖动
void findEmployeewindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        // 移动窗口
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

// 结束拖动
void findEmployeewindow::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}
void findEmployeewindow::onCloseBtnClicked()
{
    close();  // 关闭窗口
}

void findEmployeewindow::on_confirmButton_clicked()
{
    QString id=ui->lineEdit->text();
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    if(salaryManagement->getEmployee(id)!=nullptr)
    {
        mainWindowptr->setSelectedEmployee(salaryManagement->getEmployee(id));
        emit UpdateEmployeeList();
        close();
    }
    else
    {
        ui->lineEdit->setStyleSheet("border: 2px solid red;");
        ui->lineEdit->setText("未找到");
        QTimer::singleShot(2000, this, [=]() {
            ui->lineEdit->setStyleSheet("border:1px solid rgb(90, 90, 90);");
            ui->lineEdit->setText("请输入要查找的职工的ID：");
        });
        return;
    }
}

