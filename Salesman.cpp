#include "Salesman.h"

Salesman::Salesman():sales(0.0),commissionRate(0.0){}

int Salesman::type() const {
	return 3;
}

double Salesman::calcSalary() const {
	return getBasicSalary() + sales * commissionRate;
}

QString Salesman::displayInfo() const {
	return Employee::displayInfo()+ 
		QString(", Sales: %1, Rate: %2, Total: %3").arg(sales).arg(commissionRate).arg(calcSalary());
}

void Salesman::writeToStream(QDataStream& out) const {
	Employee::writeToStream(out);
	out << sales << commissionRate;
}

void Salesman::readFromStream(QDataStream& in) {
	Employee::readFromStream(in);
	in >> sales >> commissionRate;
}