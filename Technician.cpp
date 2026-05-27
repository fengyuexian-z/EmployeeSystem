#include "Technician.h"

Technician::Technician() : projectRate(0.0) {}

int Technician::type() const {
    return 2;
}

double Technician::calcSalary() const {
    return getBasicSalary() * (1 + projectRate);
}

QString Technician::displayInfo() const {
    return Employee::displayInfo() + 
        QString(", Rate: %1, Total: %2").arg(projectRate).arg(calcSalary());
}

void Technician::writeToStream(QDataStream& out) const {
    Employee::writeToStream(out);
    out << projectRate;
}

void Technician::readFromStream(QDataStream& in) {
    Employee::readFromStream(in);
    in >> projectRate;
}