#include "LoginDialog.h"
#include "PasswordManager.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMessageBox>

LoginDialog::LoginDialog(QWidget* parent) :QDialog(parent) ,attempts(0){
	setWindowTitle("登录界面");
	//基础组件
	userEdit = new QLineEdit(this);
	passEdit = new QLineEdit(this);
	passEdit->setEchoMode(QLineEdit::Password);
	QPushButton* loginbtn = new QPushButton("登录", this);
	msgLabel = new QLabel(this);
	QLabel* userlabel = new QLabel("用户名：", this);
	QLabel* passlabel = new QLabel("密码：", this);

	QGridLayout* formlayout = new QGridLayout();
	formlayout->addWidget(userlabel, 0, 0);
	formlayout->addWidget(userEdit, 0, 1);
	formlayout->addWidget(passlabel, 1, 0);
	formlayout->addWidget(passEdit, 1, 1);
	formlayout->addWidget(loginbtn, 2, 0, 1, 2, Qt::AlignCenter); // 按钮居中
	formlayout->setColumnStretch(1, 1);  // 输入框列可拉伸

	QHBoxLayout* msgLayout = new QHBoxLayout();
	msgLayout->addStretch();
	msgLayout->addWidget(msgLabel);
	msgLayout->addStretch();

	QVBoxLayout* outerLayout = new QVBoxLayout(this);
	outerLayout->addStretch(1);
	outerLayout->addLayout(formlayout, 2);
	outerLayout->addLayout(msgLayout, 1);

	//点击按钮或回车登录
	connect(loginbtn, &QPushButton::clicked, this, &LoginDialog::onLogin);
	connect(passEdit, &QLineEdit::returnPressed, this, &LoginDialog::onLogin);
}

void LoginDialog::onLogin() {
	QString username = userEdit->text();
	QString password = passEdit->text();
	//检验账密
	if (PasswordManager::validateUser(username, password)) {
		msgLabel->setText("登录成功！");
		emit loginsucceeded;
	}
	else {
		attempts++;	
		if (attempts >= 3) {
			QMessageBox::critical(this, "登录失败", "错误次数已达到上限！");
			emit loginfailed();
		}
		else {
			msgLabel->setText(QString("登录失败！剩余尝试次数：%1").arg(3 - attempts));
			userEdit->clear();
			passEdit->clear();
			userEdit->setFocus();
		}
	}
}