#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "Employee.h"

class Technician : public Employee
{
public:
    Technician();
    double projectRate;

    int type() const override;
    double calcSalary() const override;
    QString displayInfo() const override;
    void writeToStream(QDataStream& out) const override;
    void readFromStream(QDataStream& in) override;
};

#endif
