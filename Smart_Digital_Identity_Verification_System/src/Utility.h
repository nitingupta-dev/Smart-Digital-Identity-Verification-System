#pragma once

#include <string>
#include <vector>

class Utility
{
public:
    static void setColor(int colorCode);

    static void clearScreen();

    static void pauseScreen();

    static const int COLOR_TITLE   = 11;
    static const int COLOR_MENU    = 9;
    static const int COLOR_SUCCESS = 10;
    static const int COLOR_WARNING = 14;
    static const int COLOR_ERROR   = 12;
    static const int COLOR_DEFAULT = 7;

    static std::string readMaskedPassword();

    static std::string readLine();

    static std::string getCurrentDate();

    static std::string maskAadhaar(const std::string& aadhaar);

    static bool isValidName(const std::string& name);
    static bool isValidAge(int age);
    static bool isValidEmail(const std::string& email);
    static bool isValidMobile(const std::string& mobile);
    static bool isValidAadhaar(const std::string& aadhaar);
    static bool isValidPassword(const std::string& password);
    static bool isNumeric(const std::string& text);

    static std::string trim(const std::string& text);

    static std::string toLower(const std::string& text);

    static std::vector<std::string> splitString(const std::string& text, char delimiter);
};
