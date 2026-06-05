#include "EmployeeManager.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

EmployeeManager::EmployeeManager(){}
EmployeeManager::~EmployeeManager(){
	clear();
}

void EmployeeManager::clear() {
	qDeleteAll(m_employees);
	m_employees.clear();
}

bool EmployeeManager::loadFromFile(const QString& filename) {
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug()<<"员工文件读取失败！" << file.errorString();
		return false;
	}
	QDataStream in(&file);
	clear();
	while (!in.atEnd()) {
		int TypeCode = 0;
		in >> TypeCode;
		if (in.status() != QDataStream::Ok) {
			break;
		}

		Employee* e=nullptr;
		switch (TypeCode)
		{
		case 1: e = new Manager(); break;
		case 2: e = new Technician(); break;
		case 3: e = new Salesman(); break;
		default: break;
		}

		if (e) {
			e->readFromStream(in);
			m_employees.append(e);
		}
		else {
			return false;
		}
	}
	file.close();
	return true;
}

bool EmployeeManager::saveToFile(const QString& filename) const{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() << "员工文件写入失败！" << file.errorString();
		return false;
	}
	QDataStream out(&file);

	for (const Employee* e : m_employees) {
		out << e->type();
		e->writeToStream(out);
	}
	file.close();
	return true;
}

void EmployeeManager::addEmployee(Employee* e) {
	m_employees.append(e);
}
void EmployeeManager::removeEmployee(int index) {
	if (index >= 0 && index < m_employees.size()) {
		delete m_employees[index];
		m_employees.removeAt(index);
	}
}
void EmployeeManager::updateEmployee(int index, Employee* newData) {
	if (index >= 0 && index < m_employees.size()) {
		delete m_employees[index];
		m_employees[index] = newData;
	}
}

Employee* EmployeeManager::employeeAt(int index) const {
	if (index >= 0 && index < m_employees.size())
		return m_employees[index];
	return nullptr;
}

int EmployeeManager::count() const {
	return m_employees.size();
}

QVector<Employee*>& EmployeeManager::employees() {
	return m_employees;
}