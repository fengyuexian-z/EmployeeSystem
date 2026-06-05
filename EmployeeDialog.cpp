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
	//基础布局	
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	QFormLayout* form = new QFormLayout();
	idEdit = new QLineEdit(this);
	nameEdit = new QLineEdit(this);
	genderEdit = new QLineEdit(this);
	deptEdit = new QLineEdit(this);
	basicSalarySpin = new QDoubleSpinBox(this);
	basicSalarySpin->setRange(0, 9999999);
	basicSalarySpin->setDecimals(2);
	basicSalarySpin->setSuffix(tr(" 元"));
	
	form->addRow(tr("ID:"), idEdit);
	form->addRow(tr("姓名:"), nameEdit);
	form->addRow(tr("性别:"), genderEdit);
	form->addRow(tr("部门:"), deptEdit);
	form->addRow(tr("基本工资:"), basicSalarySpin);
	typeCombo = new QComboBox(this);
	typeCombo->addItem(tr("经理"), 1);      // 对应TypeCode
	typeCombo->addItem(tr("技术员"), 2);
	typeCombo->addItem(tr("销售员"), 3);
	form->addRow(tr("类型:"), typeCombo);
	mainLayout->addLayout(form);

    // 动态页面
    stack = new QStackedWidget(this);

    // 经理页面
    QWidget* ManagerPage = new QWidget();
    QFormLayout* ManagerLayout = new QFormLayout(ManagerPage);
    bonusSpin = new QDoubleSpinBox(ManagerPage);
    bonusSpin->setRange(0, 999999);
    bonusSpin->setDecimals(2);
    bonusSpin->setSuffix(tr(" 元"));
    ManagerLayout->addRow(tr("奖金:"), bonusSpin);
    stack->addWidget(ManagerPage);

    // 技术员页面
    QWidget* techPage = new QWidget();
    QFormLayout* techLayout = new QFormLayout(techPage);
    rateSpin = new QDoubleSpinBox(techPage);
    rateSpin->setRange(0, 10);
    rateSpin->setDecimals(2);
    commRateSpin->setSingleStep(0.01);
    techLayout->addRow(tr("提成比例"), rateSpin);
    stack->addWidget(techPage);

    // 销售员页面
    QWidget* salePage = new QWidget();
    QFormLayout* saleLayout = new QFormLayout(salePage);
    salesSpin = new QDoubleSpinBox(salePage);
    salesSpin->setRange(0, 999999);
    salesSpin->setDecimals(2);
    salesSpin->setSuffix(tr(" 元"));
    commRateSpin = new QDoubleSpinBox(salePage);
    commRateSpin->setRange(0, 1);
    commRateSpin->setDecimals(2);
    commRateSpin->setSuffix(tr("%"));
    commRateSpin->setSingleStep(0.01);
    saleLayout->addRow(tr("销售额:"), salesSpin);
    saleLayout->addRow(tr("提成比例:"), commRateSpin);
    stack->addWidget(salePage);

    mainLayout->addWidget(stack);

    //按钮
    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* cancelBtn = new QPushButton(tr("取消"), this);
    QPushButton* okBtn = new QPushButton(tr("确定"), this);
    btnLayout->addStretch();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(okBtn);
    mainLayout->addLayout(btnLayout);

    //信号槽连接
    connect(typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &EmployeeDialog::onTypeChanged);   
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);

    // 默认显示经理页面
    onTypeChanged(0);
}

void EmployeeDialog::onTypeChanged(int index)
{
    stack->setCurrentIndex(index);
}

void EmployeeDialog::setEmployee(const Employee* e) {
    if (!e) {
        return;
    }
    //基础信息填写
    idEdit->setText(QString::number(e->getId()));
    nameEdit->setText(e->getName());
    genderEdit->setText(e->getGender());
    deptEdit->setText(e->getDepartment());
    basicSalarySpin->setValue(e->getBasicSalary());
    //切换专属界面
    int typeIdx = e->type() - 1;
    typeCombo->setCurrentIndex(typeIdx);
    //专有信息
    switch (e->type()) {
    case 1: { // Manager
        auto mgr = dynamic_cast<const Manager*>(e);
        if (mgr) bonusSpin->setValue(mgr->bonus);
        break;
    }
    case 2: { // Technician
        auto tech = dynamic_cast<const Technician*>(e);
        if (tech) rateSpin->setValue(tech->projectRate);
        break;
    }
    case 3: { // Salesman
        auto sale = dynamic_cast<const Salesman*>(e);
        if (sale) {
            salesSpin->setValue(sale->sales);
            commRateSpin->setValue(sale->commissionRate);
        }
        break;
    }
    }
}

Employee* EmployeeDialog::getEmployee()
{
    // 验证 ID
    bool ok;
    int id = idEdit->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, tr("错误"), tr("ID必须是正整数"));
        return nullptr;
    }
    // 验证姓名
    QString name = nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, tr("错误"), tr("姓名不能为空"));
        return nullptr;
    }

    QString gender = genderEdit->text();
    QString dept = deptEdit->text();
    double basic = basicSalarySpin->value();

    int type = typeCombo->currentData().toInt();
    Employee* emp = nullptr;

    switch (type) {
    case 1: { // Manager
        Manager* m = new Manager;
        m->bonus = bonusSpin->value();
        emp = m;
        break;
    }
    case 2: { // Technician
        Technician* t = new Technician;
        double rate = rateSpin->value();
        if (rate < 0 || rate > 10) {
            QMessageBox::warning(this, tr("错误"), tr("项目费率必须在0~10之间"));
            delete t;
            return nullptr;
        }
        t->projectRate = rate;
        emp = t;
        break;
    }
    case 3: { // Salesman
        Salesman* s = new Salesman;
        double sales = salesSpin->value();
        double comm = commRateSpin->value();
        if (comm < 0 || comm > 1) {
            QMessageBox::warning(this, tr("错误"), tr("佣金率必须在0~100%之间"));
            delete s;
            return nullptr;
        }
        s->sales = sales;
        s->commissionRate = comm;
        emp = s;
        break;
    }
    default:
        return nullptr;
    }
    // 设置公共属性
    emp->setId(id);
    emp->setName(name);
    emp->setGender(gender);
    emp->setDepartment(dept);
    emp->setBasicSalary(basic);

    return emp;
}