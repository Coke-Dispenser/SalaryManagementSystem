#ifndef SALARYMANAGENMENT_H
#define SALARYMANAGENMENT_H

#endif // SALARYMANAGENMENT_H
#include<QObject>
#include <QString>
#include <QList>
#include"Employee.h"


class SalaryManagement:public QObject
{
private:

    static SalaryManagement*InstanceSM;
    QList<Employee> EmployeeList;
    const QString defaultAvatarPath=":/image/image/default.png";
public:
    static SalaryManagement*getInstance();
    SalaryManagement(){}
    void addEmployee(const Employee &employee); //增加职工
    Employee* getEmployee(const QString id);//查找职工
    bool deleteEmployee(Employee*emp);//删除职工
    QList<Employee>&getEmployeeList();//获取职工列表
    bool loadDataByMonth(const QString &month);//加载数据
    bool saveDataByMonth(const QString &month);//保存数据
    void clearEmployeeList();//清除列表
};
