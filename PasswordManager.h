#pragma once

#include <QString>

class PasswordManager {
private:
    static const QString SECRET_KEY;
    static QString encrypt(const QString& plainText);
    static QString decrypt(const QString& hexCipher);
public:
    static bool validate(const QString& username, const QString& password);
    static bool changePassword(const QString& oldPassword, const QString& newPassword);
    static void createDefaultAccount();
};