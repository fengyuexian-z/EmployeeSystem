#include "MainWindow.h"
#include "restart.h"
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>
#include <QScreen>
#include <QGuiApplication>


MainWindow::MainWindow(QWidget* parent) :QMainWindow(parent) {
	setWindowTitle("职工管理系统");
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    resize(screenGeometry.width() * 0.7, screenGeometry.height() * 0.7);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    setupLoginPage();
    stackedWidget->setCurrentIndex(0);   // 默认显示登录页
}

MainWindow::~MainWindow() {
    saveData();
}

void MainWindow::setupLoginPage() {
    loginDialog = new LoginDialog();
    connect(loginDialog, &LoginDialog::loginsucceeded, this,&MainWindow::onLoginSucceeded);
    connect(loginDialog, &LoginDialog::loginfailed, this, &MainWindow::onLoginFailed);
    //垂直居中
    QWidget* container = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(container);
    lay->addStretch();
    lay->addWidget(loginDialog, 0, Qt::AlignCenter);
    lay->addStretch();

    stackedWidget->addWidget(container);
}

void MainWindow::onLoginSucceeded() {
    setupManagePage();
    loadData();
    refreshTable();
    switchToManagePage();
}

void MainWindow::onLoginFailed() {
    close();
}

void MainWindow::switchToManagePage() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::setupManagePage() {
    // 菜单栏
    QMenu* fileMenu = menuBar()->addMenu("文件");
    QAction* exitAction = fileMenu->addAction("退出");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    QMenu* accountMenu = menuBar()->addMenu("账户");
    QAction* chgPwdAction = accountMenu->addAction("修改密码");
    connect(chgPwdAction, &QAction::triggered, this, &MainWindow::onChangePassword);
    //工具栏
    QToolBar* toolbar = addToolBar("工具栏");
    QAction* addAct = toolbar->addAction("添加");
    QAction* editAct = toolbar->addAction("修改");
    QAction* delAct = toolbar->addAction("删除");
    QAction* findAct = toolbar->addAction("查询");
    QAction* statAct = toolbar->addAction("统计");
    connect(addAct, &QAction::triggered, this, &MainWindow::onAdd);
    connect(editAct, &QAction::triggered, this, &MainWindow::onEdit);
    connect(delAct, &QAction::triggered, this, &MainWindow::onDelete);
    connect(findAct, &QAction::triggered, this, &MainWindow::onFind);
    connect(statAct, &QAction::triggered, this, &MainWindow::onStatistics);
    //员工信息
    QWidget* managePage = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(managePage);
    layout->setContentsMargins(0, 0, 0, 0);

    table = new QTableWidget();
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels({ "ID", "姓名", "性别", "部门", "基础工资", "额外信息", "实发工资","员工类型"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(table);
    //双击表格进行信息修改
    connect(table, &QTableWidget::cellDoubleClicked, this, &MainWindow::onTableDoubleClicked);

    stackedWidget->addWidget(managePage);  // 索引 1
}

void MainWindow::saveData() {
    manager.saveToFile(dataFile);
}
void MainWindow::loadData() {
    manager.loadFromFile(dataFile);
}

void MainWindow::refreshTable() {
    table->setRowCount(0);
    for (int i = 0; i < manager.count(); ++i) {
        Employee* e = manager.employeeAt(i);
        if (!e) continue;

        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(e->getId())));
        table->setItem(row, 1, new QTableWidgetItem(e->getName()));
        table->setItem(row, 2, new QTableWidgetItem(e->getGender()));
        table->setItem(row, 3, new QTableWidgetItem(e->getDepartment()));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(e->getBasicSalary(), 'f', 2)));

        QString extra;
        if (auto* m = dynamic_cast<Manager*>(e)) {
            extra = QString("管理津贴： %1").arg(m->bonus,0,'f',2);
            table->setItem(row, 7, new QTableWidgetItem("经理"));
        }
        else if (auto* t = dynamic_cast<Technician*>(e)) {
            extra = QString("项目提成： %1 %").arg(t->projectRate*100,0,'f',1);
            table->setItem(row, 7, new QTableWidgetItem("技术员"));
        }
        else if (auto* s = dynamic_cast<Salesman*>(e)) {
            extra = QString("销售额： %1, 提成比例： %2 %").arg(s->sales).arg(s->commissionRate*100,0,'f',1);
            table->setItem(row, 7, new QTableWidgetItem("销售员"));
        }
        table->setItem(row, 5, new QTableWidgetItem(extra));
        table->setItem(row, 6, new QTableWidgetItem(QString::number(e->calcSalary(), 'f', 2)));
    }
}

void MainWindow::onAdd() {
    EmployeeDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Employee* e = dlg.getEmployee();
        if (e) {
            if (!manager.addEmployee(e)) {
                QMessageBox::question(this, "警告", "id重复！");
            }
            saveData();
            refreshTable();
        }
    }
}
void MainWindow::onEdit() {
    int row = table->currentRow();
    Employee* old = manager.employeeAt(row);
    if (!old) return;

    EmployeeDialog dlg(this);
    dlg.setEmployee(old);
    if (dlg.exec() == QDialog::Accepted) {
        Employee* e = dlg.getEmployee();
        if (e) {
            if (!manager.updateEmployee(row, e)) {
                QMessageBox::question(this, "警告", "id重复！");
            }
            refreshTable();
            saveData();
        }
    }
}
void MainWindow::onDelete() {
    int row = table->currentRow();
    Employee* old = manager.employeeAt(row);
    if (!old) return;

    if (QMessageBox::question(this, "确认", "您确定要删除此员工？") == QMessageBox::Yes) {
        manager.removeEmployee(row);
        refreshTable();
        saveData();
    }
}
void MainWindow::onFind() {
    QString text = QInputDialog::getText(this, "查询", "输入 ID 或 名字 ：");
    if (text.isEmpty()) return;

    for (int i = 0; i < table->rowCount(); i++) {
        QTableWidgetItem* idItem = table->item(i, 0);
        QTableWidgetItem* nameItem = table->item(i, 1);
        if ((idItem && idItem->text() == text) || (nameItem && nameItem->text().contains(text, Qt::CaseInsensitive))) {
            table->selectRow(i);
            table->scrollToItem(idItem);
            return;
        }
    }
    QMessageBox::information(this, "查询", "未找到该员工！");
}

double MainWindow::avg(int cnt, double sum) {
    return cnt ? sum / cnt : 0.0;
}
void MainWindow::onStatistics() {
    int mgrCount = 0, techCount = 0, saleCount = 0;
    double mgrSum = 0, techSum = 0, saleSum = 0;
    for (int i = 0; i < manager.count(); ++i) {
        Employee* e = manager.employeeAt(i);
        double sal = e->calcSalary();
        switch (e->type()) {
        case 1: mgrCount++; mgrSum += sal; break;
        case 2: techCount++; techSum += sal; break;
        case 3: saleCount++; saleSum += sal; break;
        }
    }

    QString msg = QString("经理： 员工数量：%1 , 平均工资： %2\n")
        .arg(mgrCount).arg(avg(mgrCount, mgrSum), 0, 'f', 2);
    msg += QString("技术员： 员工数量：%1 , 平均工资： %2\n")
        .arg(techCount).arg(avg(techCount, techSum), 0, 'f', 2);
    msg += QString("销售员： 员工数量：%1 , 平均工资： %2\n")
        .arg(saleCount).arg(avg(saleCount, saleSum), 0, 'f', 2);
    QMessageBox::information(this, "Statistics", msg);
}

void MainWindow::AppRestart() {
    saveData();
    restartApplication();
}
void MainWindow::onChangePassword() {
    ChangePasswordDialog dlg(this);
    connect(&dlg, &ChangePasswordDialog::passwordChanged, this, &MainWindow::AppRestart);
    if (dlg.exec()==QDialog::Accepted) {      
    }
}

void MainWindow::onTableDoubleClicked(int row, int col) {
    table->selectRow(row);
    onEdit();
}