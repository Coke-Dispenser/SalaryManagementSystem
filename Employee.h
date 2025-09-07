#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QString>

#endif // EMPLOYEE_H

class Employee
{
private:
    QString EmployeeID;
    QString Name;
    QString avatarPath;
    double BaseSalary;
    double Allowances;
    double PositionAllowance;
    double Subsidies;
    double HousingAllowance;
    double TransportationAllowance;
    double GrossPay;
    double Rent;
    double Savings;
    double MembershipFees;
    double PersonalIncomeTax;
    double Deductions;
    double NetPay;

public:
    Employee(QString employeeID, const QString& name, const QString& avatarPath,
             double baseSalary, double allowances, double positionAllowance,
             double subsidies, double housingAllowance, double transportationAllowance,
             double rent, double savings, double membershipFees)
        :
        EmployeeID(employeeID),
        Name(name),
        avatarPath(avatarPath),
        BaseSalary(baseSalary),
        Allowances(allowances),
        PositionAllowance(positionAllowance),
        Subsidies(subsidies),
        HousingAllowance(housingAllowance),
        TransportationAllowance(transportationAllowance),
        Rent(rent),
        Savings(savings),
        MembershipFees(membershipFees),
        GrossPay(getGrossPay()),
        PersonalIncomeTax(getPersonalIncomeTax()),
        Deductions(getDeductions()),
        NetPay(getNetPay())
    {}
    Employee()
    {}
    //getter and setter
    QString getEmployeeID() const { return EmployeeID; }
    void setEmployeeID(QString employeeID) { EmployeeID = employeeID; }

    QString getName() const { return Name; }
    void setName(const QString &name) { Name = name; }

    QString getAvatarPath() const { return avatarPath; }
    void setAvatarPath(const QString &avatarPath) { this->avatarPath = avatarPath; }

    double getBaseSalary() const { return BaseSalary; }
    void setBaseSalary(double baseSalary) { BaseSalary = baseSalary; }

    double getAllowances() const { return Allowances; }
    void setAllowances(double allowances) { Allowances = allowances; }

    double getPositionAllowance() const { return PositionAllowance; }
    void setPositionAllowance(double positionAllowance) { PositionAllowance = positionAllowance; }

    double getSubsidies() const { return Subsidies; }
    void setSubsidies(double subsidies) { Subsidies = subsidies; }

    double getHousingAllowance() const { return HousingAllowance; }
    void setHousingAllowance(double housingAllowance) { HousingAllowance = housingAllowance; }

    double getTransportationAllowance() const { return TransportationAllowance; }
    void setTransportationAllowance(double transportationAllowance) { TransportationAllowance =transportationAllowance; }

    double getGrossPay()
    {
        return  BaseSalary+Allowances+PositionAllowance+
                Subsidies+HousingAllowance+TransportationAllowance;
    }

    double getRent() const { return Rent; }
    void setRent(double rent) { Rent = rent; }

    double getSavings() const { return Savings; }
    void setSavings(double savings) { Savings = savings; }

    double getMembershipFees() const { return MembershipFees; }
    void setMembershipFees(double membershipFees) { MembershipFees = membershipFees; }

    double getPersonalIncomeTax() ;

    double getDeductions()
    {
        return Rent+Savings+MembershipFees+getPersonalIncomeTax();;
    }

    double getNetPay()
    {

        return getGrossPay()-getDeductions();
    }
};


