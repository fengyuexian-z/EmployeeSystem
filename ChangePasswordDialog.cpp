#include "ChangePasswordDialog.h"
#include "PasswordManager.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMessageBox>

ChangePasswordDialog::ChangePasswordDialog(QWidget* parent) : QDialog(parent){
	setWindowTitle("修改密码");
	//基础组件
	oldPassEdit = new QLineEdit(this);
	newPassEdit = new QLineEdit(this);
	confirmPassEdit = new QLineEdit(this);
	QPushButton* changeBtn = new QPushButton("确认", this);

	QLabel* oldPassLabel = new QLabel("旧密码：", this);
	QLabel* newPassLabel = new QLabel("新密码：", this);
	QLabel* confirmPassLabel = new QLabel("确认新密码：", this);

	QGridLayout* formlayout = new QGridLayout();
	formlayout->addWidget(oldPassLabel, 0, 0);
	formlayout->addWidget(oldPassEdit, 0, 1);
	formlayout->addWidget(newPassLabel, 1, 0);
	formlayout->addWidget(newPassEdit, 1, 1);
	formlayout->addWidget(confirmPassLabel, 2, 0);
	formlayout->addWidget(confirmPassEdit, 2, 1);
	formlayout->addWidget(changeBtn, 3, 0, 1, 2, Qt::AlignCenter); // 按钮居中
	formlayout->setColumnStretch(1, 1);

	QVBoxLayout* outerLayout = new QVBoxLayout(this);
	outerLayout->addStretch(1);
	outerLayout->addLayout(formlayout, 2);
	outerLayout->addStretch(1);

	connect(changeBtn, &QPushButton::clicked, this, &ChangePasswordDialog::tochangpass);
	connect(confirmPassEdit, &QLineEdit::returnPressed, this, &ChangePasswordDialog::tochangpass);
}

void ChangePasswordDialog::tochangpass() {
	QString oldPass = oldPassEdit->text();
	QString newPass = newPassEdit->text();
	QString confirmPass = confirmPassEdit->text();
	if (newPass.isEmpty()) {
		QMessageBox::warning(this, "错误", "新密码不能为空！");
		newPassEdit->clear();
		confirmPassEdit->clear();
		newPassEdit->setFocus();
		return;
	}
	if (newPass != confirmPass) {
		QMessageBox::warning(this, "错误", "新密码和确认密码不匹配！");
		newPassEdit->clear();
		confirmPassEdit->clear();
		newPassEdit->setFocus();
		return;
	}
	if (!PasswordManger::changePassword(oldPass, newPass)) {
		QMessageBox::critical(this, "错误", "旧密码错误！");
		oldPassEdit->clear();
		oldPassEdit->setFocus();
		return;
	}	
	QMessageBox::information(this, "成功", "密码修改成功！");
	this->close();
}