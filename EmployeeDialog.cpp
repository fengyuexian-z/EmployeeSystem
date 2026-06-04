#include "EmployeeDialog.h"
#include "Manager.h"
#include "Technician.h"
#include "Salesman.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

EmployeeDialog::EmployeeDialog(QWidget* parent):QDialog(parent) {
	setWindowTitle("职工数据明细");
	setupUI();
	
}
void EmployeeDialog::setupUI() {

	idEdit = new QLineEdit(this);
	nameEdit = new QLineEdit(this);
	genderEdit = new QLineEdit(this);
	deptEdit = new QLineEdit(this);
	

}