#include "PasswordManager.h"
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QByteArray>

const QString PasswordManager::SECRET_KEY = "secretkey";

QString PasswordManager::encrypt(const QString& plainText) {
    QByteArray plainBytes = plainText.toUtf8();
    QByteArray keyBytes = SECRET_KEY.toUtf8();
    QByteArray result;
    int keylen = keyBytes.size();
    //循环异或加密
    for (int i = 0; i < plainBytes.size(); i++) {
        char keyChar = keyBytes[i % keylen];
        result.append(plainBytes[i] ^ keyChar);
    }
    return result.toHex();
}

QString PasswordManager::decrypt(const QString& cipherText) {
    QByteArray keyBytes = SECRET_KEY.toUtf8();
    QByteArray cipherBytes = QByteArray::fromHex(cipherText.toUtf8());
    QByteArray result;
    int keylen = keyBytes.size();
    //循环异或解密
    for (int i = 0; i < cipherText.size(); ++i) {
        char keyChar = keyBytes[i % keylen];
        result.append(cipherBytes[i] ^ keyChar);
    }
    return QString::fromUtf8(result);
}

void PasswordManager::createDefaultAccount() {
    QFile file("password.dat");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug()<<"密码文件初始化失败！"<< file.errorString();
    }
    QDataStream out(&file);
    //写入初始账密
    out << QString("admin");
    out << encrypt(QString("123456"));
    file.close();
}

bool PasswordManager::validate(const QString& username, const QString& password) {
    QFile file("password.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"密码文件读取失败！"<< file.errorString();
        return false;
    }
    QDataStream data(&file);
    QString storeuser, storeCiper;
    data >> storeuser >> storeCiper;
    file.close();
    //验证账密
    QString storepass = decrypt(storeCiper);
    if (storeuser == username && storepass == password) {
        return true;
    }
    else {
        return false;
    }
}

bool PasswordManager::changePassword(const QString& oldPassword, const QString& newPassword) {
    QFile file("password.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "密码文件读取失败！" << file.errorString();
        return false;
    }
    QDataStream data(&file);
    QString storeuser, storeCiper;
    data >> storeuser >> storeCiper;
    file.close();
    //验证密码
    QString storepass = decrypt(storeCiper);
    if (storepass != oldPassword) {
        return false;
    }
    //写入新密码
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "密码文件写入失败！" << file.errorString();
        return false;
    }
    QDataStream out(&file);
    out << storeuser;
    out << encrypt(newPassword);
    file.close();
    return true;
}