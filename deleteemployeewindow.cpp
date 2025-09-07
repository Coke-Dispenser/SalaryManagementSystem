#include "deleteemployeewindow.h"
#include "ui_deleteemployeewindow.h"

deleteEmployeewindow::deleteEmployeewindow(MainWindow *mainWin,QWidget *parent)
    : QDialog(parent),mainWindowptr(mainWin)
    , ui(new Ui::deleteEmployeewindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeButton, &QPushButton::clicked, this, &deleteEmployeewindow::onCloseBtnClicked);
    ui->selectedLabel->setAlignment(Qt::AlignCenter);
    ui->selectedLabel->setText(mainWindowptr->getSelectedEmployee()->getEmployeeID()+" "+mainWindowptr->getSelectedEmployee()->getName());
}

deleteEmployeewindow::~deleteEmployeewindow()
{
    delete ui;
}
void deleteEmployeewindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        // 记录鼠标相对于窗口的位置
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

// 实现窗口拖动
void deleteEmployeewindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        // 移动窗口
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

// 结束拖动
void deleteEmployeewindow::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}
void deleteEmployeewindow::onCloseBtnClicked()
{
    close();  // 关闭窗口
}
void deleteEmployeewindow::on_cancelButton_clicked()
{
    close();
}

//点击删除按钮
void deleteEmployeewindow::on_confirmButton_clicked()
{
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    salaryManagement->deleteEmployee(mainWindowptr->getSelectedEmployee());
    salaryManagement->saveDataByMonth(mainWindowptr->getMonthLabelText());
    mainWindowptr->setSelectedEmployee(nullptr);
    emit UpdateEmployeeList();
    close();
}

