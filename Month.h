#ifndef MONTH_H
#define MONTH_H

#endif // MONTH_H
#include<QStringList>
#include<QFile>
#include<QString>

class Month
{
private:
    static Month*InstanceMonth;

public:
    bool createMonth(const QString &month);//创建月份
    QStringList getallMonth();//获取所有月份
    bool isMonthValid(const QString &month);//检查月份是否正确
    QString getMonthFilePath(const QString &month);//获取月份文件路径
    static Month *getInstance();//实例
    Month(){}
};
