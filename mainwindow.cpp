#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "createMonthwindow.h"
#include"addEmployeewindow.h"
#include"updateemployeewindow.h"
#include"deleteemployeewindow.h"
#include"findemployeewindow.h"
#include"outputsalarywindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dragging(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeBtn, &QPushButton::clicked, this, &MainWindow::onCloseBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// 记录鼠标相对于窗口的位置
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}
// 实现窗口拖动
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}
// 结束拖动
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}
// 关闭窗口
void MainWindow::onCloseBtnClicked()
{
    close();
}
//设置列表显示
void MainWindow::SetListView()
{
    QListView *EmployeeListView = ui->EmployeeListView;
    EmployeeListView->setViewMode(QListView::IconMode);
    EmployeeListView->setIconSize(QSize(80, 80));
    EmployeeListView->setSpacing(20);
    EmployeeListView->setResizeMode(QListView::Adjust);
    EmployeeListView->setDragDropMode(QAbstractItemView::NoDragDrop);
    QStandardItemModel *model = new QStandardItemModel(this);
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    QList<Employee> employeeList = salaryManagement->getEmployeeList();
    foreach (const Employee &emp, employeeList) {
        QStandardItem *item = new QStandardItem();
        QPixmap pixmap(emp.getAvatarPath());
        if (pixmap.isNull()) {
            pixmap = QPixmap("./icons/default.png");
        }
        item->setIcon(QIcon(pixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        QString displayText = QString("%1\n%2")
                                  .arg(emp.getEmployeeID())
                                  .arg(emp.getName());
        item->setText(displayText);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
        item->setData(QVariant::fromValue((void*)&emp), Qt::UserRole);
        model->appendRow(item);
    }
    EmployeeListView->setModel(model);
}
//更新月份标签
void MainWindow::updateMonthViewLabel(const QString& month)
{
    QString labelText = QString("当前月份：%1").arg(month);
    ui->MonthViewLabel->setText(labelText);
}
//打开创建月份窗口
void MainWindow::on_createMonthButton_clicked()
{
    SelectedEmployee=nullptr;
    createMonthwindow* createWindow = new createMonthwindow(this);
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    connect(createWindow, &createMonthwindow::MonthViewLabelChange,
            this, &MainWindow::updateMonthViewLabel);
    connect(createWindow, &createMonthwindow::MonthViewLabelChange,
            salaryManagement, &SalaryManagement::clearEmployeeList);
    connect(createWindow, &createMonthwindow::MonthViewLabelChange,
            this, &MainWindow::SetListView);
    createWindow->exec();
}
//返回当前月份
QString MainWindow::getMonthLabelText() const {
    QString fullText = ui->MonthViewLabel->text();
    fullText.remove(QRegularExpression("<[^>]*>"));

    QStringList parts = fullText.split("：");
    if (parts.size() >= 2) {
        return parts[1].trimmed();
    }
    return "";
}

//打开增加职工窗口
void MainWindow::on_addEmployeeButton_clicked()
{
    if(getMonthLabelText().isEmpty())
    {
        changenlabel("请先创建或从文件中打开月份");
        return;
    }
    addEmployeewindow* createWindow = new addEmployeewindow(this);
    connect(createWindow,&addEmployeewindow::UpdateEmployeeList,this,&MainWindow::SetListView);
    createWindow->exec();
}

//点击检视信息
void MainWindow::on_EmployeeListView_clicked(const QModelIndex &index)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->EmployeeListView->model());
    QStandardItem *item = model->itemFromIndex(index);
    if (!item) return;
    QVariant data = item->data(Qt::UserRole);
    if (data.isValid())
    {
        Employee *emp = static_cast<Employee*>(data.value<void*>());
        SelectedEmployee=emp;
        ui->EmployeeIDlabel->setText("·职工编号：" + emp->getEmployeeID());
        ui->Namelabel->setText("·姓名：" + emp->getName());
        ui->BaseSalarylabel->setText("·基本工资：" + QString::number(emp->getBaseSalary()));
        ui->Allowanceslabel->setText("·津贴：" + QString::number(emp->getAllowances()));
        ui->PositionAllowancelabel->setText("·岗贴："+ QString::number(emp->getPositionAllowance()));
        ui->Subsidieslabel->setText("·补贴：" + QString::number(emp->getSubsidies()));
        ui->HousingAllowancelabel->setText("·房贴：" +QString::number(emp->getHousingAllowance()));
        ui->TransportationAllowancelabel->setText("·交通补贴：" +QString::number(emp->getTransportationAllowance()));
        ui->GrossPaylabel->setText("·应发数：" + QString::number(emp->getGrossPay()));
        ui->MembershipFeeslabel->setText("·会费：" + QString::number(emp->getMembershipFees()));
        ui->Savingslabel->setText("·储蓄：" + QString::number(emp->getSavings()));
        ui->PersonalIncomeTaxlabel->setText("·个人所得税：" + QString::number(emp->getPersonalIncomeTax()));
        ui->Rentlabel->setText("·房租：" + QString::number(emp->getRent()));
        ui->Deductionslabel->setText("·应扣数：" + QString::number(emp->getDeductions()));
        ui->NetPaylabel->setText("·实发数：" + QString::number(emp->getNetPay()));
        QPixmap pixmap(emp->getAvatarPath());
        ui->avatarlabel->setPixmap(pixmap.scaled(
            ui->avatarlabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
    qDebug()<<getSelectedEmployee();
}

//点击加载按钮
void MainWindow::on_loadDataByMonthButton_clicked()
{
    SelectedEmployee=nullptr;
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    salaryManagement->saveDataByMonth(getMonthLabelText());
    QString FilePath=QFileDialog::getOpenFileName(this,"选择文件",QDir::currentPath(),
                                                    "文本文件(*.txt)");
    salaryManagement->clearEmployeeList();
    SetListView();
    salaryManagement->loadDataByMonth(QFileInfo(FilePath).baseName());
    updateMonthViewLabel(QFileInfo(FilePath).baseName());
    SetListView();
}

//当前选中的员工
Employee* MainWindow::getSelectedEmployee()
{
    return SelectedEmployee;
}
//修改当前选中的员工
void MainWindow::setSelectedEmployee(Employee*emp)
{
    SelectedEmployee=emp;
}

//打开修改信息窗口
void MainWindow::on_updateEmployeeButton_clicked()
{
    if(getMonthLabelText().isEmpty())
    {
        changenlabel("请先创建或从文件中打开月份");
        return;
    }
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    if(salaryManagement->getEmployeeList().isEmpty())
    {
        changenlabel("请先添加职工");
        return;
    }
    if(getSelectedEmployee()==nullptr)
    {
        changenlabel("请先选中职工");
        return;
    }
    updateEmployeewindow* createWindow = new updateEmployeewindow(this);
    connect(createWindow,&updateEmployeewindow::UpdateEmployeeList,this,&MainWindow::SetListView);
    connect(createWindow,&updateEmployeewindow::UpdateEmployeeList,this,&MainWindow::setInfoView);
    createWindow->exec();
}
//改变提示信息标签
void MainWindow::changenlabel(const QString text)
{
    ui->SaveLabel->setText(text);
    QTimer::singleShot(1000, this, [=]() {
        ui->SaveLabel->setText("");
    });
}

//打开删除职工窗口
void MainWindow::on_deleteEmployeeButton_clicked()
{
    if(getMonthLabelText().isEmpty())
    {
        changenlabel("请先创建或从文件中打开月份");
        return;
    }
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    if(salaryManagement->getEmployeeList().isEmpty())
    {
        changenlabel("请先添加职工");
        return;
    }
    if(getSelectedEmployee()==nullptr)
    {
        changenlabel("请先选中职工");
        return;
    }
    deleteEmployeewindow* createWindow = new deleteEmployeewindow(this);
    connect(createWindow,&deleteEmployeewindow::UpdateEmployeeList,this,&MainWindow::SetListView);
    connect(createWindow,&deleteEmployeewindow::UpdateEmployeeList,this,&MainWindow::setInfoView);
    createWindow->exec();
}

//打开查找窗口
void MainWindow::on_getEmployeeButton_clicked()
{
    if(getMonthLabelText().isEmpty())
    {
        changenlabel("请先创建或从文件中打开月份");
        return;
    }
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    if(salaryManagement->getEmployeeList().isEmpty())
    {
        changenlabel("请先添加职工");
        return;
    }
    findEmployeewindow* createWindow = new findEmployeewindow(this);
    connect(createWindow,&findEmployeewindow::UpdateEmployeeList,this,&MainWindow::setInfoView);
    createWindow->exec();
}
//设置显示信息
void MainWindow::setInfoView()
{
    if(SelectedEmployee!=nullptr)
    {
    Employee*emp=SelectedEmployee;
    ui->EmployeeIDlabel->setText("·职工编号：" + emp->getEmployeeID());
    ui->Namelabel->setText("·姓名：" + emp->getName());
    ui->BaseSalarylabel->setText("·基本工资：" + QString::number(emp->getBaseSalary()));
    ui->Allowanceslabel->setText("·津贴：" + QString::number(emp->getAllowances()));
    ui->PositionAllowancelabel->setText("·岗贴："+ QString::number(emp->getPositionAllowance()));
    ui->Subsidieslabel->setText("·补贴：" + QString::number(emp->getSubsidies()));
    ui->HousingAllowancelabel->setText("·房贴：" +QString::number(emp->getHousingAllowance()));
    ui->TransportationAllowancelabel->setText("·交通补贴：" +QString::number(emp->getTransportationAllowance()));
    ui->GrossPaylabel->setText("·应发数：" + QString::number(emp->getGrossPay()));
    ui->MembershipFeeslabel->setText("·会费：" + QString::number(emp->getMembershipFees()));
    ui->Savingslabel->setText("·储蓄：" + QString::number(emp->getSavings()));
    ui->PersonalIncomeTaxlabel->setText("·个人所得税：" + QString::number(emp->getPersonalIncomeTax()));
    ui->Rentlabel->setText("·房租：" + QString::number(emp->getRent()));
    ui->Deductionslabel->setText("·应扣数：" + QString::number(emp->getDeductions()));
    ui->NetPaylabel->setText("·实发数：" + QString::number(emp->getNetPay()));
    QPixmap pixmap(emp->getAvatarPath());
    ui->avatarlabel->setPixmap(pixmap.scaled(
        ui->avatarlabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        ));
    }
    else
    {
        ui->EmployeeIDlabel->setText("·职工编号：" );
        ui->Namelabel->setText("·姓名：" );
        ui->BaseSalarylabel->setText("·基本工资：" );
        ui->Allowanceslabel->setText("·津贴：");
        ui->PositionAllowancelabel->setText("·岗贴：");
        ui->Subsidieslabel->setText("·补贴：");
        ui->HousingAllowancelabel->setText("·房贴：");
        ui->TransportationAllowancelabel->setText("·交通补贴：" );
        ui->GrossPaylabel->setText("·应发数：");
        ui->MembershipFeeslabel->setText("·会费：");
        ui->Savingslabel->setText("·储蓄：" );
        ui->PersonalIncomeTaxlabel->setText("·个人所得税：");
        ui->Rentlabel->setText("·房租：" );
        ui->Deductionslabel->setText("·应扣数：");
        ui->NetPaylabel->setText("·实发数：");
        ui->avatarlabel->setPixmap(QPixmap());
    }
}
//打开输出窗口
void MainWindow::on_outputSalaryButton_clicked()
{
    if(getMonthLabelText().isEmpty())
    {
        changenlabel("请先创建或从文件中打开月份");
        return;
    }
    SalaryManagement* salaryManagement = SalaryManagement::getInstance();
    if(salaryManagement->getEmployeeList().isEmpty())
    {
        changenlabel("请先添加职工");
        return;
    }
    outputSalarywindow* createWindow = new outputSalarywindow(this);
    createWindow->exec();
}

