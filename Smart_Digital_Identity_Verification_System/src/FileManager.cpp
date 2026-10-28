#include "FileManager.h"
#include "Utility.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

const std::string FileManager::CITIZENS_FILE = "data/citizens.txt";
const std::string FileManager::ADMINS_FILE    = "data/admins.txt";
const std::string FileManager::REPORT_FILE    = "data/report.txt";

std::vector<Citizen> FileManager::loadCitizens(const std::string& filePath)
{
    std::vector<Citizen> citizens;
    std::ifstream inFile(filePath);

    if (!inFile.is_open())
    {
        return citizens;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(inFile, line))
    {
        ++lineNumber;

        if (Utility::trim(line).empty())
        {
            continue;
        }

        try
        {
            citizens.push_back(Citizen::fromFileRecord(line));
        }
        catch (const std::exception& ex)
        {
            Utility::setColor(Utility::COLOR_WARNING);
            std::cout << "Warning: Skipping corrupted record at line "
                      << lineNumber << " in " << filePath
                      << " (" << ex.what() << ")\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
        }
    }

    inFile.close();
    return citizens;
}

bool FileManager::saveCitizens(const std::vector<Citizen>& citizens, const std::string& filePath)
{
    std::ofstream outFile(filePath, std::ios::trunc);

    if (!outFile.is_open())
    {
        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << "Error: Could not open " << filePath << " for writing.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
        return false;
    }

    for (const Citizen& citizen : citizens)
    {
        outFile << citizen.toFileRecord() << "\n";
    }

    outFile.close();
    return true;
}

Admin FileManager::loadAdmin(const std::string& filePath)
{
    std::ifstream inFile(filePath);

    if (!inFile.is_open())
    {
        Admin defaultAdmin = Admin::createDefaultAdmin();
        saveAdmin(defaultAdmin, filePath);
        return defaultAdmin;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (Utility::trim(line).empty())
        {
            continue;
        }

        std::vector<std::string> fields = Utility::splitString(line, '|');

        if (fields.size() != 2)
        {
            Utility::setColor(Utility::COLOR_WARNING);
            std::cout << "Warning: Corrupted admin record in " << filePath
                      << ". Using default admin credentials.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);

            Admin defaultAdmin = Admin::createDefaultAdmin();
            saveAdmin(defaultAdmin, filePath);
            return defaultAdmin;
        }

        inFile.close();
        return Admin(fields[0], fields[1]);
    }

    inFile.close();
    Admin defaultAdmin = Admin::createDefaultAdmin();
    saveAdmin(defaultAdmin, filePath);
    return defaultAdmin;
}

bool FileManager::saveAdmin(const Admin& admin, const std::string& filePath)
{
    std::ofstream outFile(filePath, std::ios::trunc);

    if (!outFile.is_open())
    {
        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << "Error: Could not open " << filePath << " for writing.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
        return false;
    }

    outFile << admin.getUsername() << "|" << admin.getPassword() << "\n";
    outFile.close();
    return true;
}

bool FileManager::writeLines(const std::string& filePath, const std::vector<std::string>& lines)
{
    std::ofstream outFile(filePath, std::ios::trunc);

    if (!outFile.is_open())
    {
        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << "Error: Could not open " << filePath << " for writing.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
        return false;
    }

    for (const std::string& line : lines)
    {
        outFile << line << "\n";
    }

    outFile.close();
    return true;
}

bool FileManager::fileExists(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    return inFile.good();
}