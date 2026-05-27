#include "Manager.h"

Manager::Manager():bonus(0.0){}

int Manager::type() const{ 
	return 1; 
}

double Manager::calcSalary() const { 
	return getBasicSalary() + bonus; 
}

QString Manager::displayInfo() const {
	return Employee::displayInfo() + QString(", Bonus: %1, Total: %2").arg(bonus).arg(calcSalary());
}

void Manager::writeToStream(QDataStream& out) const {
	Employee::writeToStream(out);
	out << bonus;
}

void Manager::readFromStream(QDataStream& in) {
	Employee::readFromStream(in);
	in >> bonus;
}