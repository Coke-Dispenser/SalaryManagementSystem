#include"SalaryManagenment.h"
#include"Month.h"

SalaryManagement*SalaryManagement::InstanceSM=nullptr;

SalaryManagement*SalaryManagement::getInstance()
{
    if(InstanceSM==nullptr)
        InstanceSM=new SalaryManagement();
    return InstanceSM;
}
void SalaryManagement::addEmployee(const Employee &employee)
{
    Employee NewEmployee=employee;
    if(NewEmployee.getAvatarPath().isEmpty())
    {
        NewEmployee.setAvatarPath(defaultAvatarPath);
    }
    EmployeeList.append(NewEmployee);
}
Employee* SalaryManagement::getEmployee(const QString id)
{
    for(int i=0;i<EmployeeList.size();i++)
    {
        if(EmployeeList[i].getEmployeeID()==id)
            return &EmployeeList[i];
    }
    return nullptr;
}
bool SalaryManagement::deleteEmployee(Employee*emp)
{
    if (!emp) {
        return false;
    }
    QString id = emp->getEmployeeID();
    for (int i = 0; i < EmployeeList.size(); ++i) {
        if (EmployeeList[i].getEmployeeID() == id) {
            EmployeeList.removeAt(i);
            qDebug() << "删除成功";
            return true;
        }
    }
    qDebug() << "未找到该id";
    return false;
}
QList<Employee>&SalaryManagement::getEmployeeList()
{
    return EmployeeList;
}
bool SalaryManagement::loadDataByMonth(const QString &month)
{
    QString FilePath=Month::getInstance()->getMonthFilePath(month);
    QFile File(FilePath);
    if(!File.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return false;
    }
    QTextStream in(&File);
    EmployeeList.clear();
    while(!in.atEnd())
    {
        QString Line=in.readLine().trimmed();
        if (Line.isEmpty())
            continue;
        QStringList parts=Line.split(",");
        if(parts.size()!=15)
        {
            qDebug()<<"格式错误";
            continue;
        }
        QString employeeID=parts[0];
        QString name=parts[1];
        QString avatarPath=parts[2];
        double baseSalary=parts[3].toDouble();
        double allowances=parts[4].toDouble();
        double positionAllowance=parts[5].toDouble();
        double subsidies=parts[6].toDouble();
        double housingAllowance=parts[7].toDouble();
        double transportationAllowance=parts[8].toDouble();
        double rent=parts[9].toDouble();
        double savings=parts[10].toDouble();
        double membershipFees=parts[11].toDouble();
        EmployeeList.append(Employee(employeeID, name,avatarPath,
            baseSalary,allowances, positionAllowance,
            subsidies,  housingAllowance,  transportationAllowance,
            rent, savings,  membershipFees));
    }
    File.close();
    return true;
}
bool SalaryManagement::saveDataByMonth(const QString &month)
{
    QString FilePath=Month::getInstance()->getMonthFilePath(month);
    QFile File(FilePath);
    if(!File.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return false;
    }
    QTextStream out(&File);
    for(int i=0;i<EmployeeList.size();i++)
    {
        out<<EmployeeList[i].getEmployeeID()<<","
            <<EmployeeList[i].getName()<<","
            <<EmployeeList[i].getAvatarPath()<<","
            <<EmployeeList[i].getBaseSalary()<<","
            <<EmployeeList[i].getAllowances()<<","
            <<EmployeeList[i].getPositionAllowance()<<","
            <<EmployeeList[i].getSubsidies()<<","
            <<EmployeeList[i].getHousingAllowance()<<","
            <<EmployeeList[i].getTransportationAllowance()<<","
            <<EmployeeList[i].getRent()<<","
            <<EmployeeList[i].getSavings()<<","
            <<EmployeeList[i].getMembershipFees()<<","
            <<EmployeeList[i].getGrossPay()<<","
            <<EmployeeList[i].getDeductions()<<","
            <<EmployeeList[i].getNetPay()
            <<'\n';
    }
    File.close();
    return true;
}
void SalaryManagement::clearEmployeeList()
{
    EmployeeList.clear();
}



// 输出单个员工薪资到Excel
void SalaryManagement::outputEmployeeSalary(Employee* emp)
{
    // 创建Excel应用
    QAxObject* excel = new QAxObject("Excel.Application");
    excel->setProperty("Visible", false); // 不显示Excel窗口

    // 创建工作簿
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Add");
    QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1); // 获取第一个工作表

    // 设置文件名
    QString fileName = QString("%1 %2.xlsx")
                           .arg(emp->getEmployeeID())
                           .arg(emp->getName());
    QString filePath = QDir::currentPath() + '/' + fileName;

    // 准备数据
    QStringList row;
    row << emp->getEmployeeID()
        << emp->getName()
        << QString::number(emp->getBaseSalary())
        << QString::number(emp->getAllowances())
        << QString::number(emp->getPositionAllowance())
        << QString::number(emp->getSubsidies())
        << QString::number(emp->getHousingAllowance())
        << QString::number(emp->getTransportationAllowance())
        << QString::number(emp->getGrossPay())
        << QString::number(emp->getRent())
        << QString::number(emp->getSavings())
        << QString::number(emp->getMembershipFees())
        << QString::number(emp->getPersonalIncomeTax())
        << QString::number(emp->getDeductions())
        << QString::number(emp->getNetPay());

    // 写入表头
    for (int i = 0; i < headers.size(); ++i) {
        QAxObject* cell = worksheet->querySubObject("Cells(int, int)", 1, i + 1);
        cell->setProperty("Value", headers[i]);
        delete cell;
    }

    // 写入数据
    for (int i = 0; i < row.size(); ++i) {
        QAxObject* cell = worksheet->querySubObject("Cells(int, int)", 2, i + 1);
        cell->setProperty("Value", row[i]);
        delete cell;
    }

    // 保存并关闭
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    // 清理资源
    delete worksheet;
    delete workbook;
    delete workbooks;
    delete excel;
}

// 输出月度薪资到Excel
void SalaryManagement::outputMonthSalary(const QString &month)
{
    // 创建Excel应用
    QAxObject* excel = new QAxObject("Excel.Application");
    excel->setProperty("Visible", false); // 不显示Excel窗口

    // 创建工作簿
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Add");
    QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1); // 获取第一个工作表

    // 设置文件名
    QString fileName = month.trimmed() + "月工资明细.xlsx";
    QString filePath = QDir::currentPath() + '/' + fileName;

    // 计算总工资
    double totalSalary = 0.0;
    for(const auto& emp : EmployeeList) {
        totalSalary += emp.getNetPay();
    }

    // 写入表头
    for (int i = 0; i < headers.size(); ++i) {
        QAxObject* cell = worksheet->querySubObject("Cells(int, int)", 1, i + 1);
        cell->setProperty("Value", headers[i]);
        delete cell;
    }

    // 写入员工数据
    int rowIndex = 2; // 从第2行开始（第1行是表头）
    for (const auto& emp : EmployeeList) {
        QStringList row;
        row << emp.getEmployeeID()
            << emp.getName()
            << QString::number(emp.getBaseSalary())
            << QString::number(emp.getAllowances())
            << QString::number(emp.getPositionAllowance())
            << QString::number(emp.getSubsidies())
            << QString::number(emp.getHousingAllowance())
            << QString::number(emp.getTransportationAllowance())
            << QString::number(emp.getGrossPay())
            << QString::number(emp.getRent())
            << QString::number(emp.getSavings())
            << QString::number(emp.getMembershipFees())
            << QString::number(emp.getPersonalIncomeTax())
            << QString::number(emp.getDeductions())
            << QString::number(emp.getNetPay());

        // 写入一行数据
        for (int colIndex = 0; colIndex < row.size(); ++colIndex) {
            QAxObject* cell = worksheet->querySubObject("Cells(int, int)", rowIndex, colIndex + 1);
            cell->setProperty("Value", row[colIndex]);
            delete cell;
        }

        rowIndex++;
    }

    // 写入总计
    QString totalStr = QString("%1月总工资 %2 元").arg(month).arg(totalSalary);
    QAxObject* totalCell = worksheet->querySubObject("Cells(int, int)", rowIndex + 1, 1);
    totalCell->setProperty("Value", totalStr);
    delete totalCell;

    // 保存并关闭
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    // 清理资源
    delete worksheet;
    delete workbook;
    delete workbooks;
    delete excel;
}
