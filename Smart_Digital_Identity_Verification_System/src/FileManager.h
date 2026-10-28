#pragma once

#include "Citizen.h"
#include "Admin.h"
#include <vector>
#include <string>

class FileManager
{
public:
    static const std::string CITIZENS_FILE;
    static const std::string ADMINS_FILE;
    static const std::string REPORT_FILE;

    static std::vector<Citizen> loadCitizens(const std::string& filePath = CITIZENS_FILE);
    static bool saveCitizens(const std::vector<Citizen>& citizens,
                              const std::string& filePath = CITIZENS_FILE);

    static Admin loadAdmin(const std::string& filePath = ADMINS_FILE);
    static bool saveAdmin(const Admin& admin, const std::string& filePath = ADMINS_FILE);

    static bool writeLines(const std::string& filePath, const std::vector<std::string>& lines);
    static bool fileExists(const std::string& filePath);
};