#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDataStream>

class Employee
{
public:
    Employee();
    virtual ~Employee();
    //员工信息
    void setId(int id);
    void setName(const QString& name);
    void setGender(const QString& gender);
    void setDepartment(const QString& dept);
    void setBasicSalary(double basic);

    int getId() const;
    QString getName() const;
    QString getGender() const;
    QString getDepartment() const;
    double getBasicSalary() const;


    virtual int type() const = 0;   //员工类型编号
    virtual double calcSalary() const = 0;  //总工资
    virtual QString displayInfo() const;
    //文件读写
    virtual void writeToStream(QDataStream& out) const;
    virtual void readFromStream(QDataStream& in);

private:
    int id;
    QString name;
    QString gender;
    QString department;
    double basicSalary;
};

#endif 