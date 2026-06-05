#include "restart.h"
#include <QProcess>
#include <QCoreApplication>
#include <QTimer>

void restartApplication(int delayMs) {
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();

    QProcess::startDetached(program, arguments);

    // 延迟退出，确保新进程有足够时间启动
    QTimer::singleShot(delayMs, QCoreApplication::quit);
}