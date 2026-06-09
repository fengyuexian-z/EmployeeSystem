#include "Employee.h"

Employee::Employee() :id(0), basicSalary(0.0){}
Employee::~Employee(){}

void Employee::setId(int id) { this->id = id; }
void Employee::setName(const QString& name) { this->name = name; }
void Employee::setGender(const QString& gender) { this->gender = gender; }
void Employee::setDepartment(const QString& dept) { this->department = dept; }
void Employee::setBasicSalary(double basic) { this->basicSalary = basic; }

int Employee::getId() const { return id; }
QString Employee::getName() const { return name; }
QString Employee::getGender() const { return gender; }
QString Employee::getDepartment() const { return department; }
double Employee::getBasicSalary() const { return basicSalary; }

QString Employee::displayInfo() const {
    return QString("ID: %1, Name: %2, Gender: %3, Dept: %4, Basic: %5")
        .arg(id).arg(name).arg(gender).arg(department).arg(basicSalary);
}

void Employee::writeToStream(QDataStream& out) const {
    out << id << name << gender << department << basicSalary;
}

void Employee::readFromStream(QDataStream& in) {
    in >> id >> name >> gender >> department >> basicSalary;
}