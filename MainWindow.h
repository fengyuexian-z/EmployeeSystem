#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStackedWidget>
#include "EmployeeManager.h"
#include "LoginDialog.h"
#include "EmployeeDialog.h"
#include "ChangePasswordDialog.h"
#include "PasswordManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginSucceeded();
    void onLoginFailed();
    void onAdd();
    void onEdit();
    void onDelete();
    void onFind();
    void onStatistics();
    void onChangePassword();
    void onTableDoubleClicked(int row, int col);

private:
    void setupLoginPage();
    void setupManagePage();
    void refreshTable();
    void saveData();
    void loadData();
    void switchToManagePage();

    QStackedWidget* stackedWidget;
    LoginDialog* loginDialog;    

    QTableWidget* table;
    EmployeeManager manager;
    const QString dataFile = "employees.dat";
};

#endif