#pragma once

#include <QString>

class PasswordManager {
    static const QString KEY;
    static QString encrypt(const QString& plainText);
    static QString decrypt(const QString& hexCipher);
    static bool validate(const QString& username, const QString& password);
    static bool changePassword(const QString& oldPassword, const QString& newPassword);
    static void createDefaultAccount();
};