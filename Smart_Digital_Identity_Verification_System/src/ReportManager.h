#pragma once

#include "Citizen.h"
#include "FileManager.h"
#include <vector>
#include <string>

class ReportManager
{
public:
    struct ReportData
    {
        int totalCitizens        = 0;
        int verifiedCitizens     = 0;
        int pendingCitizens      = 0;
        int rejectedCitizens     = 0;
        int todaysRegistrations  = 0;
    };

    static ReportData generateReport(const std::vector<Citizen>& citizens);

    static void displayReport(const ReportData& report);

    static bool exportReport(const ReportData& report,
                              const std::string& filePath = FileManager::REPORT_FILE);
};
