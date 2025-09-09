#include "Employee.h"

double Employee::getPersonalIncomeTax() const
{
    double base=getBaseSalary();
    double personalIncomeTax=0.0;
    if (base <= 800) {
        personalIncomeTax = 0.0;
    }
    else if (base <= 1000) {
        personalIncomeTax = (base - 800) * 0.05;
    }
    else if (base <= 5000) {
        personalIncomeTax += (1000 - 800) * 0.05;
        personalIncomeTax += (base - 1000) * 0.10;
    }
    else {
        personalIncomeTax += (1000 - 800) * 0.05;
        personalIncomeTax += (5000 - 1000) * 0.10;
        personalIncomeTax += (base - 5000) * 0.20;
    }

    return personalIncomeTax;

}
