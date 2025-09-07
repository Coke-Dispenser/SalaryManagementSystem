#include"SalaryManagenment.h"
#include"Month.h"
#include<QString>
#include<Qfile>
#include<QDebug>
#include<QStringList>
#include<QTextStream>

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
    // 检查空指针
    if (!emp) {
        qDebug() << "传入的员工工为空指针";
        return false;
    }

    QString id = emp->getEmployeeID();

    // 遍历查找并删除
    for (int i = 0; i < EmployeeList.size(); ++i) {
        if (EmployeeList[i].getEmployeeID() == id) {

            // 从容器中移除对象
            EmployeeList.removeAt(i);
            qDebug() << "删除成功";
            return true;
        }
    }

    // 循环结束仍未找到
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
