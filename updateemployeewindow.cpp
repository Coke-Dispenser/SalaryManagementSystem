#include "updateemployeewindow.h"
#include "ui_updateemployeewindow.h"


updateEmployeewindow::updateEmployeewindow(MainWindow *mainWin,QWidget *parent)
    : QDialog(parent), mainWindowptr(mainWin)
    , ui(new Ui::updateEmployeewindow)
{
    ui->setupUi(this);
    QString Path=mainWindowptr->getSelectedEmployee()->getAvatarPath();
    QPixmap pix(Path);
    if (!pix.isNull()) {
        ui->imageLabel->setPixmap(pix.scaled(
            ui->imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
    setplaceholderText();
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeButton, &QPushButton::clicked, this, &updateEmployeewindow::onCloseBtnClicked);
}

updateEmployeewindow::~updateEmployeewindow()
{
    delete ui;
}
void updateEmployeewindow::on_selectImageBtn_clicked()
{
    imagePath="";
    imagePath=QFileDialog::getOpenFileName(this,"选择图片",QDir::homePath(),
                                             "图片文件(*.png *.jpg *.jpeg *.bmp);;所有文件(*.*)");
    if(!imagePath.isEmpty())
    {
        QPixmap pixmap(imagePath);
        if(!pixmap.isNull())
        {
            QPixmap scalePix=pixmap.scaled(
                ui->imageLabel->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation);
            ui->imageLabel->setPixmap(scalePix);
        }
        else
        {
            ui->imageLabel->setText("图片加载失败");
        }
    }
}
void updateEmployeewindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        // 记录鼠标相对于窗口的位置
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

// 实现窗口拖动
void updateEmployeewindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        // 移动窗口
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

// 结束拖动
void updateEmployeewindow::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}
void updateEmployeewindow::onCloseBtnClicked()
{
    close();  // 关闭窗口
}
void updateEmployeewindow::on_confirmButton_clicked()
{
    if(mainWindowptr->getSelectedEmployee()==nullptr)
    {
        mainWindowptr->changenlabel();
        close();
    }
    Employee*emp=mainWindowptr->getSelectedEmployee();
    if(!mainWindowptr->getMonthLabelText().isNull())
    {
        emp->setEmployeeID(getEffectiveText(ui->EmployeeIDlineEdit));
        emp->setName(getEffectiveText(ui->NamelineEdit));
        if(imagePath!=""){emp->setAvatarPath(imagePath);}
        emp->setBaseSalary(getEffectiveText(ui->BaseSalarylineEdit).toDouble());
        emp->setAllowances(getEffectiveText(ui->AllowanceslineEdit).toDouble());
        emp->setPositionAllowance(getEffectiveText(ui->PositionAllowancelineEdit).toDouble());
        emp->setSubsidies(getEffectiveText(ui->SubsidieslineEdit).toDouble());
        emp->setHousingAllowance(getEffectiveText(ui->HousingAllowancelineEdit).toDouble());
        emp->setTransportationAllowance(getEffectiveText(ui->TransportationAllowancelineEdit).toDouble());
        emp->setRent(getEffectiveText(ui->RentlineEdit).toDouble());
        emp->setSavings(getEffectiveText(ui->SavinglineEdit).toDouble());
        emp->setMembershipFees(getEffectiveText(ui->MembershipFeeslineEdit).toDouble());
        SalaryManagement* SalaryManagementInstance =SalaryManagement::getInstance();
        SalaryManagementInstance->saveDataByMonth(mainWindowptr->getMonthLabelText());
        emit UpdateEmployeeList();
    }
    close();
}
QString updateEmployeewindow::getEffectiveText(QLineEdit *lineEdit)
{
    QString input = lineEdit->text().trimmed();
    if (input.isEmpty()) {
        return lineEdit->placeholderText();
    } else {
        return input;
    }
}
void updateEmployeewindow::setplaceholderText()
{    if(mainWindowptr->getSelectedEmployee()==nullptr)
    {
        mainWindowptr->changenlabel();
        close();
    }
    Employee*emp=mainWindowptr->getSelectedEmployee();
    ui->EmployeeIDlineEdit->setPlaceholderText(emp->getEmployeeID());
    ui->NamelineEdit->setPlaceholderText(emp->getName());
    ui->BaseSalarylineEdit->setPlaceholderText(QString::number(emp->getBaseSalary()));
    ui->AllowanceslineEdit->setPlaceholderText( QString::number(emp->getAllowances()));
    ui->PositionAllowancelineEdit->setPlaceholderText( QString::number(emp->getPositionAllowance()));
    ui->SubsidieslineEdit->setPlaceholderText(QString::number(emp->getSubsidies()));
    ui->HousingAllowancelineEdit->setPlaceholderText(QString::number(emp->getHousingAllowance()));
    ui->TransportationAllowancelineEdit->setPlaceholderText(QString::number(emp->getTransportationAllowance()));
    ui->MembershipFeeslineEdit->setPlaceholderText(QString::number(emp->getMembershipFees()));
    ui->SavinglineEdit->setPlaceholderText(QString::number(emp->getSavings()));
    ui->RentlineEdit->setPlaceholderText(QString::number(emp->getRent()));
}
