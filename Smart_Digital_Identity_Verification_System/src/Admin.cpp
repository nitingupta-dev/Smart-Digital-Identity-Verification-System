#include "Admin.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>

static const std::string DEFAULT_ADMIN_USERNAME = "admin";
static const std::string DEFAULT_ADMIN_PASSWORD = "admin123";

Admin::Admin()
    : Citizen(), username("")
{
}

Admin::Admin(const std::string& username, const std::string& password)
    : Citizen(), username(username)
{
    setPassword(password);
}

Admin::~Admin()
{
}

std::string Admin::getUsername() const
{
    return username;
}

bool Admin::verifyCredentials(const std::string& inputUsername,
                               const std::string& inputPassword) const
{
    return username == inputUsername && verifyPassword(inputPassword);
}

void Admin::displayProfile() const
{
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== ADMIN PROFILE ========================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::cout << std::left << std::setw(22) << "Username" << ": " << username << "\n";
    std::cout << std::left << std::setw(22) << "Role"     << ": Administrator\n";

    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "=============================================================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);
}

Admin Admin::createDefaultAdmin()
{
    return Admin(DEFAULT_ADMIN_USERNAME, DEFAULT_ADMIN_PASSWORD);
}
