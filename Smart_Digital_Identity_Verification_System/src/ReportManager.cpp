#include "ReportManager.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>

ReportManager::ReportData ReportManager::generateReport(const std::vector<Citizen>& citizens)
{
    ReportData report;
    std::string today = Utility::getCurrentDate();

    report.totalCitizens = static_cast<int>(citizens.size());

    for (const Citizen& citizen : citizens)
    {
        switch (citizen.getVerificationStatus())
        {
            case VerificationStatus::VERIFIED:
                ++report.verifiedCitizens;
                break;
            case VerificationStatus::REJECTED:
                ++report.rejectedCitizens;
                break;
            case VerificationStatus::PENDING:
            default:
                ++report.pendingCitizens;
                break;
        }

        if (citizen.getRegistrationDate() == today)
        {
            ++report.todaysRegistrations;
        }
    }

    return report;
}

void ReportManager::displayReport(const ReportData& report)
{
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== SYSTEM REPORT =========================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::cout << std::left << std::setw(28) << "Total Citizens"        << ": " << report.totalCitizens << "\n";

    Utility::setColor(Utility::COLOR_SUCCESS);
    std::cout << std::left << std::setw(28) << "Verified Citizens"     << ": " << report.verifiedCitizens << "\n";
    Utility::setColor(Utility::COLOR_WARNING);
    std::cout << std::left << std::setw(28) << "Pending Citizens"      << ": " << report.pendingCitizens << "\n";
    Utility::setColor(Utility::COLOR_ERROR);
    std::cout << std::left << std::setw(28) << "Rejected Citizens"     << ": " << report.rejectedCitizens << "\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::cout << std::left << std::setw(28) << "Today's Registrations" << ": " << report.todaysRegistrations << "\n";

    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "=============================================================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);
}

bool ReportManager::exportReport(const ReportData& report, const std::string& filePath)
{
    std::vector<std::string> lines;

    lines.push_back("=====================================");
    lines.push_back("   SMART DIGITAL IDENTITY VERIFICATION");
    lines.push_back("           SYSTEM REPORT");
    lines.push_back("=====================================");
    lines.push_back("Generated On          : " + Utility::getCurrentDate());
    lines.push_back("-------------------------------------");
    lines.push_back("Total Citizens        : " + std::to_string(report.totalCitizens));
    lines.push_back("Verified Citizens     : " + std::to_string(report.verifiedCitizens));
    lines.push_back("Pending Citizens      : " + std::to_string(report.pendingCitizens));
    lines.push_back("Rejected Citizens     : " + std::to_string(report.rejectedCitizens));
    lines.push_back("Today's Registrations : " + std::to_string(report.todaysRegistrations));
    lines.push_back("=====================================");

    return FileManager::writeLines(filePath, lines);
}
