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
	QPushButton* loginbtn=new QPushButton("登录", this);
	msgLabel = new QLabel(this);
	QLabel* userlabel = new QLabel("用户名：", this);
	QLabel* passlabel = new QLabel("密码：", this);
	msgLabel = new QLabel(this);
	//布局
	QHBoxLayout* userlayout = new QHBoxLayout(this);
	userlayout->addWidget(userlabel);
	userlayout->addWidget(userEdit);

	QHBoxLayout* passlayout = new QHBoxLayout(this);
	passlayout->addWidget(passlabel);
	passlayout->addWidget(passEdit);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addStretch();
	layout->addLayout(userlayout);
	layout->addLayout(passlayout);
	layout->addWidget(loginbtn);
	layout->addWidget(msgLabel);
	layout->addStretch();
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