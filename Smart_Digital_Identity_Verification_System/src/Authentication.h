#pragma once

#include "Citizen.h"
#include "Admin.h"
#include <vector>
#include <string>

class Authentication
{
public:
    static bool registerCitizen(std::vector<Citizen>& citizens);

    static Citizen* loginCitizen(std::vector<Citizen>& citizens);

    static bool loginAdmin(const Admin& admin);

    static bool forgotPassword(std::vector<Citizen>& citizens);

private:
    static const int MAX_ATTEMPTS = 3;

    static bool isEmailTaken(const std::vector<Citizen>& citizens, const std::string& email);
    static bool isMobileTaken(const std::vector<Citizen>& citizens, const std::string& mobile);
    static bool isAadhaarTaken(const std::vector<Citizen>& citizens, const std::string& aadhaar);

    static Citizen* findByEmail(std::vector<Citizen>& citizens, const std::string& email);

    static std::string promptValidName();
    static int         promptValidAge();
    static std::string promptValidGender();
    static std::string promptNonEmpty(const std::string& fieldLabel);
    static std::string promptValidMobile(const std::vector<Citizen>& citizens);
    static std::string promptValidEmail(const std::vector<Citizen>& citizens);
    static std::string promptValidAadhaar(const std::vector<Citizen>& citizens);
    static std::string promptValidNewPassword();
};
