#include "Authentication.h"
#include "Utility.h"
#include <iostream>

bool Authentication::isEmailTaken(const std::vector<Citizen>& citizens, const std::string& email)
{
    std::string target = Utility::toLower(email);
    for (const Citizen& citizen : citizens)
    {
        if (Utility::toLower(citizen.getEmail()) == target)
        {
            return true;
        }
    }
    return false;
}

bool Authentication::isMobileTaken(const std::vector<Citizen>& citizens, const std::string& mobile)
{
    for (const Citizen& citizen : citizens)
    {
        if (citizen.getMobile() == mobile)
        {
            return true;
        }
    }
    return false;
}

bool Authentication::isAadhaarTaken(const std::vector<Citizen>& citizens, const std::string& aadhaar)
{
    for (const Citizen& citizen : citizens)
    {
        if (citizen.getAadhaarNumber() == aadhaar)
        {
            return true;
        }
    }
    return false;
}

Citizen* Authentication::findByEmail(std::vector<Citizen>& citizens, const std::string& email)
{
    std::string target = Utility::toLower(email);
    for (Citizen& citizen : citizens)
    {
        if (Utility::toLower(citizen.getEmail()) == target)
        {
            return &citizen;
        }
    }
    return nullptr;
}

std::string Authentication::promptValidName()
{
    std::string name;
    while (true)
    {
        std::cout << "Full Name: ";
        name = Utility::readLine();

        if (Utility::isValidName(name))
        {
            return name;
        }

        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << "Invalid name. Use letters and spaces only.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
    }
}

int Authentication::promptValidAge()
{
    while (true)
    {
        std::cout << "Age: ";
        std::string input = Utility::readLine();

        try
        {
            int age = std::stoi(input);
            if (Utility::isValidAge(age))
            {
                return age;
            }
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "Age must be at least 18.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
        }
        catch (const std::exception&)
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "Invalid age. Please enter a number.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
        }
    }
}

std::string Authentication::promptValidGender()
{
    std::string gender;
    while (true)
    {
        std::cout << "Gender (Male/Female/Other): ";
        gender = Utility::readLine();

        if (!gender.empty())
        {
            return gender;
        }

        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << "Gender cannot be empty.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
    }
}

std::string Authentication::promptNonEmpty(const std::string& fieldLabel)
{
    std::string value;
    while (true)
    {
        std::cout << fieldLabel << ": ";
        value = Utility::readLine();

        if (!value.empty())
        {
            return value;
        }

        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << fieldLabel << " cannot be empty.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
    }
}

std::string Authentication::promptValidMobile(const std::vector<Citizen>& citizens)
{
    std::string mobile;
    while (true)
    {
        std::cout << "Mobile Number (10 digits): ";
        mobile = Utility::readLine();

        if (!Utility::isValidMobile(mobile))
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "Mobile number must contain exactly 10 digits.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            continue;
        }

        if (isMobileTaken(citizens, mobile))
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "This mobile number is already registered.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            continue;
        }

        return mobile;
    }
}

std::string Authentication::promptValidEmail(const std::vector<Citizen>& citizens)
{
    std::string email;
    while (true)
    {
        std::cout << "Email Address: ";
        email = Utility::readLine();

        if (!Utility::isValidEmail(email))
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "Invalid email format.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            continue;
        }

        if (isEmailTaken(citizens, email))
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "This email is already registered.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            continue;
        }

        return email;
    }
}

std::string Authentication::promptValidAadhaar(const std::vector<Citizen>& citizens)
{
    std::string aadhaar;
    while (true)
    {
        std::cout << "Aadhaar Number (12 digits): ";
        aadhaar = Utility::readLine();

        if (!Utility::isValidAadhaar(aadhaar))
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "Aadhaar number must contain exactly 12 digits.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            continue;
        }

        if (isAadhaarTaken(citizens, aadhaar))
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "This Aadhaar number is already registered.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            continue;
        }

        return aadhaar;
    }
}

std::string Authentication::promptValidNewPassword()
{
    while (true)
    {
        std::cout << "New Password (min 6 characters): ";
        std::string password = Utility::readMaskedPassword();

        if (!Utility::isValidPassword(password))
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "Password must be at least 6 characters.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            continue;
        }

        std::cout << "Confirm Password: ";
        std::string confirm = Utility::readMaskedPassword();

        if (password != confirm)
        {
            Utility::setColor(Utility::COLOR_ERROR);
            std::cout << "Passwords do not match. Please try again.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            continue;
        }

        return password;
    }
}

bool Authentication::registerCitizen(std::vector<Citizen>& citizens)
{
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== CITIZEN REGISTRATION =================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::string name             = promptValidName();
    int         age              = promptValidAge();
    std::string gender           = promptValidGender();
    std::string dateOfBirth      = promptNonEmpty("Date of Birth (DD-MM-YYYY)");
    std::string mobile           = promptValidMobile(citizens);
    std::string email            = promptValidEmail(citizens);
    std::string aadhaar          = promptValidAadhaar(citizens);
    std::string address          = promptNonEmpty("Address");
    std::string password         = promptValidNewPassword();
    std::string securityQuestion = promptNonEmpty("Security Question");
    std::string securityAnswer   = promptNonEmpty("Security Answer");

    std::string citizenID        = Citizen::generateCitizenID(static_cast<int>(citizens.size()) + 1);
    std::string registrationDate = Utility::getCurrentDate();

    Citizen newCitizen(citizenID, name, age, gender, dateOfBirth, mobile,
                       email, address, password, securityQuestion,
                       securityAnswer, aadhaar, registrationDate);

    citizens.push_back(newCitizen);

    Utility::setColor(Utility::COLOR_SUCCESS);
    std::cout << "\nRegistration successful! Your Citizen ID is: " << citizenID << "\n";
    std::cout << "Verification Status: Pending\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    return true;
}

Citizen* Authentication::loginCitizen(std::vector<Citizen>& citizens)
{
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== CITIZEN LOGIN =========================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::cout << "Email (or type 'F' for Forgot Password): ";
    std::string email = Utility::readLine();

    if (Utility::toLower(email) == "f")
    {
        forgotPassword(citizens);
        return nullptr;
    }

    Citizen* citizen = findByEmail(citizens, email);

    if (citizen == nullptr)
    {
        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << "No citizen account found with this email.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
        return nullptr;
    }

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt)
    {
        std::cout << "Password: ";
        std::string password = Utility::readMaskedPassword();

        if (citizen->verifyPassword(password))
        {
            Utility::setColor(Utility::COLOR_SUCCESS);
            std::cout << "Login successful. Welcome, " << citizen->getName() << "!\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            return citizen;
        }

        int remaining = MAX_ATTEMPTS - attempt;
        Utility::setColor(Utility::COLOR_ERROR);
        if (remaining > 0)
        {
            std::cout << "Incorrect password. " << remaining << " attempt(s) remaining.\n";
        }
        else
        {
            std::cout << "Incorrect password. No attempts remaining.\n";
        }
        Utility::setColor(Utility::COLOR_DEFAULT);
    }

    Utility::setColor(Utility::COLOR_ERROR);
    std::cout << "Account login locked for this session. Please try again later.\n";
    Utility::setColor(Utility::COLOR_DEFAULT);
    return nullptr;
}

bool Authentication::loginAdmin(const Admin& admin)
{
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== ADMIN LOGIN ===========================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::cout << "Username: ";
    std::string username = Utility::readLine();

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt)
    {
        std::cout << "Password: ";
        std::string password = Utility::readMaskedPassword();

        if (admin.verifyCredentials(username, password))
        {
            Utility::setColor(Utility::COLOR_SUCCESS);
            std::cout << "Admin login successful.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            return true;
        }

        int remaining = MAX_ATTEMPTS - attempt;
        Utility::setColor(Utility::COLOR_ERROR);
        if (remaining > 0)
        {
            std::cout << "Incorrect credentials. " << remaining << " attempt(s) remaining.\n";
        }
        else
        {
            std::cout << "Incorrect credentials. No attempts remaining.\n";
        }
        Utility::setColor(Utility::COLOR_DEFAULT);
    }

    Utility::setColor(Utility::COLOR_ERROR);
    std::cout << "Admin login locked for this session. Please try again later.\n";
    Utility::setColor(Utility::COLOR_DEFAULT);
    return false;
}

bool Authentication::forgotPassword(std::vector<Citizen>& citizens)
{
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== FORGOT PASSWORD =======================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::cout << "Registered Email: ";
    std::string email = Utility::readLine();

    Citizen* citizen = findByEmail(citizens, email);

    if (citizen == nullptr)
    {
        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << "No citizen account found with this email.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
        return false;
    }

    std::cout << "Security Question: " << citizen->getSecurityQuestion() << "\n";

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt)
    {
        std::cout << "Your Answer: ";
        std::string answer = Utility::readLine();

        if (citizen->verifySecurityAnswer(answer))
        {
            std::string newPassword = promptValidNewPassword();
            citizen->setPassword(newPassword);

            Utility::setColor(Utility::COLOR_SUCCESS);
            std::cout << "Password reset successful. You can now log in.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            return true;
        }

        int remaining = MAX_ATTEMPTS - attempt;
        Utility::setColor(Utility::COLOR_ERROR);
        if (remaining > 0)
        {
            std::cout << "Incorrect answer. " << remaining << " attempt(s) remaining.\n";
        }
        else
        {
            std::cout << "Incorrect answer. No attempts remaining.\n";
        }
        Utility::setColor(Utility::COLOR_DEFAULT);
    }

    Utility::setColor(Utility::COLOR_ERROR);
    std::cout << "Password reset failed.\n";
    Utility::setColor(Utility::COLOR_DEFAULT);
    return false;
}
