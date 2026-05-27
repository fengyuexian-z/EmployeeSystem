#ifndef SALESMAN_H
#define SALESMAN_H

#include "Employee.h"

class Salesman :public Employee {
public:
	Salesman();
	double sales;
	double commissionRate;

	int type() const override;
	double calcSalary() const override;
	QString displayInfo() const override;
	void writeToStream(QDataStream& out) const override;
	void readFromStream(QDataStream& in) override;
};

#endif

