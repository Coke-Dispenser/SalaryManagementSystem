#include "Employee.h"

double Employee::getPersonalIncomeTax()
{
    double base=getBaseSalary();
    PersonalIncomeTax=0.0;
    if (base <= 800) {
        PersonalIncomeTax = 0.0;
    }
    else if (base <= 1000) {
        PersonalIncomeTax = (base - 800) * 0.05;
    }
    else if (base <= 5000) {
        PersonalIncomeTax += (1000 - 800) * 0.05;
        PersonalIncomeTax += (base - 1000) * 0.10;
    }
    else {
        PersonalIncomeTax += (1000 - 800) * 0.05;
        PersonalIncomeTax += (5000 - 1000) * 0.10;
        PersonalIncomeTax += (base - 5000) * 0.20;
    }

    return PersonalIncomeTax;

}
