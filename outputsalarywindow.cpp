#include "outputsalarywindow.h"
#include "ui_outputsalarywindow.h"

outputSalarywindow::outputSalarywindow(MainWindow *mainWin,QWidget *parent)
    : QDialog(parent),mainWindowptr(mainWin)
    , ui(new Ui::outputSalarywindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeButton, &QPushButton::clicked, this, &outputSalarywindow::onCloseBtnClicked);
}

outputSalarywindow::~outputSalarywindow()
{
    delete ui;
}
void outputSalarywindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        // 记录鼠标相对于窗口的位置
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

// 实现窗口拖动
void outputSalarywindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        // 移动窗口
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

// 结束拖动
void outputSalarywindow::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}
void outputSalarywindow::onCloseBtnClicked()
{
    close();  // 关闭窗口
}


void outputSalarywindow::on_outputEmployeeSalary_clicked()
{
    if(mainWindowptr->getSelectedEmployee()==nullptr)
    {
        mainWindowptr->changenlabel("请先选中职工");
        return;
    }
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    salaryManagement->outputEmployeeSalary(mainWindowptr->getSelectedEmployee());
    mainWindowptr->changenlabel("输出成功");
    close();
}



void outputSalarywindow::on_outputMonthSalary_clicked()
{
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    salaryManagement->outputMonthSalary(mainWindowptr->getMonthLabelText());
    mainWindowptr->changenlabel("输出成功");
    close();
}

