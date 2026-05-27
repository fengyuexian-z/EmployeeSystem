#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget* parent = nullptr);

private slots:
    void onLogin();

private:
    QLineEdit* userEdit;
    QLineEdit* passEdit;
    QLabel* msgLabel;
    int attempts;
};


#endif