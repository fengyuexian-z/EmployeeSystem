#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QStackedWidget>
#include <QDoubleSpinBox>
#include "Employee.h"

class EmployeeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EmployeeDialog(QWidget* parent = nullptr);
    void setEmployee(const Employee* e);
    Employee* getEmployee();

private slots:
    void onTypeChanged(int index);

private:
    QLineEdit* idEdit, * nameEdit, * genderEdit, * deptEdit;
    QDoubleSpinBox* basicSalarySpin;
    QComboBox* typeCombo;
    QStackedWidget* stack;

    QDoubleSpinBox* bonusSpin;       // Manager
    QDoubleSpinBox* rateSpin;        // Technician
    QDoubleSpinBox* salesSpin, * commRateSpin; // Salesman

    void setupUI();
};
