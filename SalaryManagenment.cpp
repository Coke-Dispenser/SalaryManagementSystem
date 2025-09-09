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
void SalaryManagement::outputEmployeeSalary(Employee* emp)
{
    auto getDisplayWidth = [](const QString& str) {
        int width = 0;
        foreach (const QChar& c, str) {
            if (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5) {
                width += 2;
            } else {
                width += 1;
            }
        }
        return width;
    };
    QString fileName = QString("%1 %2.txt")
                           .arg(emp->getEmployeeID())
                           .arg(emp->getName());
    QFile File(QDir::currentPath() + '/' + fileName);

    if(!File.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qDebug() << "打开文件失败";
        return;
    }
    QTextStream out(&File);
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
    QList<int> columnWidths;
    for (int i = 0; i < headers.size() && i < row.size(); ++i) {
        int headerWidth = getDisplayWidth(headers[i]);
        int dataWidth = getDisplayWidth(row[i]);
        columnWidths << qMax(headerWidth, dataWidth) + 2; // 加2作为边距
    }
    for (int width : columnWidths) {
        out << QString(width, '-');
    }
    out << "\n";
    for (int i = 0; i < headers.size() && i < columnWidths.size(); ++i) {
        QString header = headers[i];
        int spacesNeeded = columnWidths[i] - getDisplayWidth(header);
        out << header << QString(spacesNeeded, ' ');
    }
    out << "\n";
    for (int width : columnWidths) {
        out << QString(width, '-');
    }
    out << "\n";
    for (int i = 0; i < row.size() && i < columnWidths.size(); ++i) {
        QString cellData = row[i];
        int dataWidth = getDisplayWidth(cellData);
        int spacesNeeded = columnWidths[i] - dataWidth;
        if (i >= 2) {
            out << QString(spacesNeeded, ' ') << cellData;
        } else {
            out << cellData << QString(spacesNeeded, ' ');
        }
    }
    out << "\n";
    for (int width : columnWidths) {
        out << QString(width, '-');
    }
    out << "\n";

    File.close();
}
void SalaryManagement::outputMonthSalary(const QString &month)
{
    double SumSalary = 0.0;
    for(int i = 0; i < EmployeeList.size(); i++)
    {
        SumSalary += EmployeeList[i].getNetPay();
    }
    QFile File(QDir::currentPath() + '/' + month.trimmed() + "月工资明细.txt");
    if(!File.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qDebug() << "打开文件失败";
        return;
    }
    QTextStream out(&File);
    QList<QStringList> data;
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
        data << row;
    }
    QList<int> columnWidths;
    for (int i = 0; i < headers.size(); ++i) {
        auto calculateWidth = [](const QString& str) {
            int width = 0;
            foreach (const QChar& c, str) {
                if (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5) {
                    width += 2;
                } else {
                    width += 1;
                }
            }
            return width;
        };

        int maxWidth = calculateWidth(headers[i]);
        for (const auto& row : data) {
            if (i < row.size()) {
                int dataWidth = calculateWidth(row[i]);
                if (dataWidth > maxWidth) {
                    maxWidth = dataWidth;
                }
            }
        }
        columnWidths << maxWidth + 2;
    }
    for (int width : columnWidths) {
        out << QString(width, '-');
    }
    out << "\n";

    for (int i = 0; i < headers.size(); ++i) {
        QString header = headers[i];
        int headerWidth = 0;
        foreach (const QChar& c, header) {
            headerWidth += (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5) ? 2 : 1;
        }
        int spacesNeeded = columnWidths[i] - headerWidth;
        out << header << QString(spacesNeeded, ' ');
    }
    out << "\n";
    for (int width : columnWidths) {
        out << QString(width, '-');
    }
    out << "\n";
    for (const auto& row : data) {
        for (int i = 0; i < row.size(); ++i) {
            QString cellData = row[i];
            int dataWidth = 0;
            foreach (const QChar& c, cellData) {
                dataWidth += (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5) ? 2 : 1;
            }
            int spacesNeeded = columnWidths[i] - dataWidth;

            if (i >= 2) {
                out << QString(spacesNeeded, ' ') << cellData;
            } else {
                out << cellData << QString(spacesNeeded, ' ');
            }
        }
        out << "\n";
    }
    for (int width : columnWidths) {
        out << QString(width, '-');
    }
    out << "\n";
    int totalWidth = 0;
    for (int width : columnWidths) {
        totalWidth += width;
    }
    QString totalStr = month + "月总工资 " + QString::number(SumSalary) + " 元";
    int totalStrWidth = 0;
    foreach (const QChar& c, totalStr) {
        totalStrWidth += (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5) ? 2 : 1;
    }
    int totalSpaces = totalWidth - totalStrWidth;
    out << QString(totalSpaces, ' ') << totalStr << "\n";

    File.close();
}

