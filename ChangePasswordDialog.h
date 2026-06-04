#pragma once
#include <QLineEdit>
#include <QDialog>

class ChangePasswordDialog : public QDialog
{
	Q_OBJECT
public:
	explicit ChangePasswordDialog(QWidget* parent = nullptr);
signals:
	void passwordChanged();
private slots:
	void tochangpass();
private:
	QLineEdit* oldPassEdit;
	QLineEdit* newPassEdit;
	QLineEdit* confirmPassEdit;
};