#include "MainWindow.h"

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
    //窗口默认占屏幕水平、垂直的中心的1/3
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenRect = screen->availableGeometry();
    int w = screenRect.width() * 0.33;
    int h = screenRect.height() * 0.33;
    resize(w, h);
    move((screenRect.width() - w) / 2, (screenRect.height() - h) / 2);


    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    setupLoginPage();
    setupManagePage();
    stackedWidget->setCurrentIndex(0);   // 默认显示登录页
}

MainWindow::~MainWindow() {
    saveData();
}

