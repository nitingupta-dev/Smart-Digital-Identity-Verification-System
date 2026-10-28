#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cctype>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void Utility::setColor(int colorCode)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(colorCode));
#else
    (void)colorCode;
#endif
}

void Utility::clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Utility::pauseScreen()
{
    setColor(COLOR_MENU);
    std::cout << "\nPress any key to continue...";
    setColor(COLOR_DEFAULT);

#ifdef _WIN32
    _getch();
#else
    system("stty raw -echo");
    getchar();
    system("stty cooked echo");
#endif
    std::cout << std::endl;
}

std::string Utility::readMaskedPassword()
{
    std::string password;
    char ch;

#ifdef _WIN32
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!password.empty())
            {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            password.push_back(ch);
            std::cout << '*';
        }
    }
#else
    termios oldt{};
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (std::cin.get(ch) && ch != '\n')
    {
        if (ch == 127 || ch == '\b')
        {
            if (!password.empty())
            {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    std::cout << std::endl;
    return password;
}

std::string Utility::readLine()
{
    std::string line;
    std::getline(std::cin, line);
    return trim(line);
}

std::string Utility::getCurrentDate()
{
    std::time_t now = std::time(nullptr);

    std::tm* localTime = std::localtime(&now);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << localTime->tm_mday << "-"
        << std::setfill('0') << std::setw(2) << (localTime->tm_mon + 1) << "-"
        << (localTime->tm_year + 1900);

    return oss.str();
}

std::string Utility::maskAadhaar(const std::string& aadhaar)
{
    if (aadhaar.length() != 12)
    {
        return aadhaar;
    }

    std::string masked = aadhaar.substr(0, 4) + "********" + aadhaar.substr(8, 4);
    return masked;
}

bool Utility::isValidName(const std::string& name)
{
    if (name.empty())
    {
        return false;
    }

    for (char ch : name)
    {
        if (!std::isalpha(static_cast<unsigned char>(ch)) && ch != ' ' && ch != '.')
        {
            return false;
        }
    }
    return true;
}

bool Utility::isValidAge(int age)
{
    return age >= 18 && age <= 120;
}

bool Utility::isValidEmail(const std::string& email)
{
    size_t atPos = email.find('@');
    if (atPos == std::string::npos || atPos == 0)
    {
        return false;
    }

    size_t dotPos = email.find_last_of('.');
    if (dotPos == std::string::npos || dotPos < atPos)
    {
        return false;
    }

    if (dotPos == email.length() - 1)
    {
        return false;
    }

    if (email.find(' ') != std::string::npos)
    {
        return false;
    }

    return true;
}

bool Utility::isValidMobile(const std::string& mobile)
{
    return mobile.length() == 10 && isNumeric(mobile);
}

bool Utility::isValidAadhaar(const std::string& aadhaar)
{
    return aadhaar.length() == 12 && isNumeric(aadhaar);
}

bool Utility::isValidPassword(const std::string& password)
{
    return password.length() >= 6;
}

bool Utility::isNumeric(const std::string& text)
{
    if (text.empty())
    {
        return false;
    }

    for (char ch : text)
    {
        if (!std::isdigit(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }
    return true;
}

std::string Utility::trim(const std::string& text)
{
    size_t start = text.find_first_not_of(" \t\n\r");
    if (start == std::string::npos)
    {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\n\r");
    return text.substr(start, end - start + 1);
}

std::string Utility::toLower(const std::string& text)
{
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(),
                    [](unsigned char ch) { return std::tolower(ch); });
    return result;
}

std::vector<std::string> Utility::splitString(const std::string& text, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}