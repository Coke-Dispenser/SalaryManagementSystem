#include"Month.h"
#include<QFileInfo>
#include<QDir>
#include<QDebug>
#include<QString>

Month*Month::InstanceMonth=nullptr;
Month* Month::getInstance()
{
    if(InstanceMonth==nullptr)
        InstanceMonth=new Month();
    return InstanceMonth;
}
bool Month::createMonth(const QString &month)
{
    if(!isMonthValid(month))
        return false;
    QString FilePath=getMonthFilePath(month);
    QFile File(FilePath);
    if(!File.open(QIODevice::WriteOnly|QIODevice::Text))
    {qDebug()<<"创建失败";return false;}
    File.close();
    return true;
}

QStringList Month::getallMonth()
{
    QDir currentDir = QDir::currentPath();
    QStringList fileNames = currentDir.entryList({"*.txt"}, QDir::Files);
    QStringList MonthList;
    foreach (const QString &fileName, fileNames) {
        QFileInfo fileInfo(fileName);
        MonthList<< fileInfo.baseName();
    }
    return MonthList;
}

bool Month::isMonthValid(const QString& month)
{
    bool ok;
    int monthNum = month.toInt(&ok);
    if (!ok)
    {
        qDebug() << "输入不是有效的数字";
        return false;
    }
    if(monthNum<1||monthNum>12)
    { qDebug()<<"月份不正确";return false;}
    QDir currentDir = QDir::currentPath();
    if(currentDir.exists(month+".txt") )
    {qDebug()<<"月份已存在";return false;}
    return true;
}

QString Month::getMonthFilePath(const QString &month)
{
    return QDir::currentPath()+'/'+month.trimmed()+".txt";
    qDebug()<<QDir::currentPath()+'/'+month.trimmed()+".txt";
}
