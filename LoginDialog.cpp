#include "LoginDialog.h"
#include "PasswordManager.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMessageBox>

LoginDialog::LoginDialog(QWidget* parent) :QDialog(parent) ,attempts(0){
	setWindowTitle("登录界面");

	userEdit = new QLineEdit(this);
	passEdit = new QLineEdit(this);
	passEdit->setEchoMode(QLineEdit::Password);
	QPushButton* loginbtn=new QPushButton("登录", this);
	msgLabel = new QLabel(this);
	QLabel* userlabel = new QLabel("用户名：", this);
	QLabel* passlabel = new QLabel("密码：", this);

	QHBoxLayout* userlayout = new QHBoxLayout(this);
	userlayout->addWidget(userlabel);
	userlayout->addWidget(userEdit);

	QHBoxLayout* passlayout = new QHBoxLayout(this);
	passlayout->addWidget(passlabel);
	passlayout->addWidget(passEdit);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addLayout(userlayout);
	layout->addLayout(passlayout);
	layout->addWidget(loginbtn);
}

void LoginDialog::onLogin() {

}