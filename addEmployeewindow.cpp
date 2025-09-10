#include "addEmployeewindow.h"
#include "ui_addEmployeewindow.h"


addEmployeewindow::addEmployeewindow(MainWindow *mainWin, QWidget *parent)
    : QDialog(parent), mainWindowptr(mainWin)
    , ui(new Ui::addEmployeewindow)
{
    ui->setupUi(this);
    QPixmap pix(imagePath);
    ui->imageLabel->setPixmap(pix.scaled(
    ui->imageLabel->size(),
    Qt::KeepAspectRatio,
    Qt::SmoothTransformation));

    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeButton, &QPushButton::clicked, this, &addEmployeewindow::onCloseBtnClicked);
}

addEmployeewindow::~addEmployeewindow()
{
    delete ui;
}

void addEmployeewindow::on_selectImageBtn_clicked()
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
            imagePath=":/image/image/default.png";
        }
    }
}
void addEmployeewindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        // 记录鼠标相对于窗口的位置
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

// 实现窗口拖动
void addEmployeewindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        // 移动窗口
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

// 结束拖动
void addEmployeewindow::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}
void addEmployeewindow::onCloseBtnClicked()
{
    close();  // 关闭窗口
}



void addEmployeewindow::on_confirmButton_clicked()
{
    if(ui->EmployeeIDlineEdit->text().isEmpty())
    {
        ui->EmployeeIDlineEdit->setStyleSheet("border: 2px solid red;");
        QTimer::singleShot(1000, this, [=]() {
            ui->EmployeeIDlineEdit->setStyleSheet("border:1px solid rgb(90, 90, 90);");
        });
        return;
    }
    if(ui->NamelineEdit->text().isEmpty())
    {
        ui->NamelineEdit->setStyleSheet("border: 2px solid red;");
        QTimer::singleShot(1000, this, [=]() {
            ui->NamelineEdit->setStyleSheet("border:1px solid rgb(90, 90, 90);");
        });
        return;
    }
    if(!mainWindowptr->getMonthLabelText().isNull())
    {
    QString EmployeeID=ui->EmployeeIDlineEdit->text();
    QString Name=ui->NamelineEdit->text();
    QString avatarPath=imagePath;
    double BaseSalary=ui->BaseSalarylineEdit->text().toDouble();
    double Allowances=ui->AllowanceslineEdit->text().toDouble();
    double PositionAllowance=ui->PositionAllowancelineEdit->text().toDouble();
    double Subsidies=ui->SubsidieslineEdit->text().toDouble();
    double HousingAllowance=ui->HousingAllowancelineEdit->text().toDouble();
    double TransportationAllowance=ui->TransportationAllowancelineEdit->text().toDouble();
    double Rent=ui->RentlineEdit->text().toDouble();
    double Savings=ui->SavinglineEdit->text().toDouble();
    double MembershipFees=ui->MembershipFeeslineEdit->text().toDouble();
    Employee NewEmployee(EmployeeID, Name,avatarPath,
                         BaseSalary,Allowances, PositionAllowance,
                        Subsidies,  HousingAllowance,  TransportationAllowance,
                         Rent, Savings,  MembershipFees);
    SalaryManagement* SalaryManagementInstance =SalaryManagement::getInstance();
    SalaryManagementInstance->addEmployee(NewEmployee);
    SalaryManagementInstance->saveDataByMonth(mainWindowptr->getMonthLabelText());
    }
    emit UpdateEmployeeList();
    close();
}

