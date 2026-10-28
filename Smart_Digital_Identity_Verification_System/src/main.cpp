#include "Utility.h"
#include "Person.h"
#include "Citizen.h"
#include "Admin.h"
#include "Authentication.h"
#include "Verification.h"
#include "FileManager.h"
#include "ReportManager.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

static std::string toUpperCopy(const std::string& text)
{
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(),
                    [](unsigned char ch) { return static_cast<char>(std::toupper(ch)); });
    return result;
}

static Citizen* findCitizenById(std::vector<Citizen>& citizens, const std::string& id)
{
    std::string target = toUpperCopy(Utility::trim(id));
    for (Citizen& citizen : citizens)
    {
        if (toUpperCopy(citizen.getCitizenID()) == target)
        {
            return &citizen;
        }
    }
    return nullptr;
}

static int promptMenuChoice(const std::string& prompt, int minOption, int maxOption)
{
    while (true)
    {
        Utility::setColor(Utility::COLOR_MENU);
        std::cout << prompt;
        Utility::setColor(Utility::COLOR_DEFAULT);

        std::string input = Utility::readLine();

        try
        {
            int choice = std::stoi(input);
            if (choice >= minOption && choice <= maxOption)
            {
                return choice;
            }
        }
        catch (const std::exception&)
        {
        }

        Utility::setColor(Utility::COLOR_ERROR);
        std::cout << "Invalid choice. Please enter a number between "
                  << minOption << " and " << maxOption << ".\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
    }
}

static bool promptYesNo(const std::string& question)
{
    std::cout << question << " (Y/N): ";
    std::string answer = Utility::readLine();
    return !answer.empty() && (answer[0] == 'Y' || answer[0] == 'y');
}

static void printWelcomeBanner()
{
    Utility::clearScreen();
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n";
    std::cout << "===================================================\n";
    std::cout << "     SMART DIGITAL IDENTITY VERIFICATION SYSTEM     \n";
    std::cout << "===================================================\n";
    std::cout << "   Secure. Verified. Digital Identity for Citizens. \n";
    std::cout << "===================================================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);
}

static void updateProfileMenu(Citizen& citizen, std::vector<Citizen>& citizens)
{
    Utility::clearScreen();
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== UPDATE PROFILE ========================\n";
    Utility::setColor(Utility::COLOR_MENU);
    std::cout << "1. Update Mobile\n";
    std::cout << "2. Update Email\n";
    std::cout << "3. Update Address\n";
    std::cout << "4. Update Password\n";
    std::cout << "5. Back to Dashboard\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    int choice = promptMenuChoice("Enter your choice: ", 1, 5);

    switch (choice)
    {
        case 1:
        {
            std::cout << "New Mobile Number (10 digits): ";
            std::string mobile = Utility::readLine();

            if (!Utility::isValidMobile(mobile))
            {
                Utility::setColor(Utility::COLOR_ERROR);
                std::cout << "Invalid mobile number. Update cancelled.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                break;
            }

            bool taken = false;
            for (const Citizen& other : citizens)
            {
                if (other.getCitizenID() != citizen.getCitizenID() && other.getMobile() == mobile)
                {
                    taken = true;
                    break;
                }
            }

            if (taken)
            {
                Utility::setColor(Utility::COLOR_ERROR);
                std::cout << "This mobile number is already registered to another citizen.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                break;
            }

            citizen.setMobile(mobile);
            FileManager::saveCitizens(citizens);
            Utility::setColor(Utility::COLOR_SUCCESS);
            std::cout << "Mobile number updated successfully.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            break;
        }
        case 2:
        {
            std::cout << "New Email Address: ";
            std::string email = Utility::readLine();

            if (!Utility::isValidEmail(email))
            {
                Utility::setColor(Utility::COLOR_ERROR);
                std::cout << "Invalid email format. Update cancelled.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                break;
            }

            bool taken = false;
            std::string target = Utility::toLower(email);
            for (const Citizen& other : citizens)
            {
                if (other.getCitizenID() != citizen.getCitizenID() &&
                    Utility::toLower(other.getEmail()) == target)
                {
                    taken = true;
                    break;
                }
            }

            if (taken)
            {
                Utility::setColor(Utility::COLOR_ERROR);
                std::cout << "This email is already registered to another citizen.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                break;
            }

            citizen.setEmail(email);
            FileManager::saveCitizens(citizens);
            Utility::setColor(Utility::COLOR_SUCCESS);
            std::cout << "Email address updated successfully.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            break;
        }
        case 3:
        {
            std::cout << "New Address: ";
            std::string address = Utility::readLine();

            if (address.empty())
            {
                Utility::setColor(Utility::COLOR_ERROR);
                std::cout << "Address cannot be empty. Update cancelled.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                break;
            }

            citizen.setAddress(address);
            FileManager::saveCitizens(citizens);
            Utility::setColor(Utility::COLOR_SUCCESS);
            std::cout << "Address updated successfully.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            break;
        }
        case 4:
        {
            std::cout << "Current Password: ";
            std::string currentPassword = Utility::readMaskedPassword();

            if (!citizen.verifyPassword(currentPassword))
            {
                Utility::setColor(Utility::COLOR_ERROR);
                std::cout << "Current password is incorrect. Update cancelled.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                break;
            }

            std::cout << "New Password (min 6 characters): ";
            std::string newPassword = Utility::readMaskedPassword();

            if (!Utility::isValidPassword(newPassword))
            {
                Utility::setColor(Utility::COLOR_ERROR);
                std::cout << "Password must be at least 6 characters. Update cancelled.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                break;
            }

            std::cout << "Confirm New Password: ";
            std::string confirmPassword = Utility::readMaskedPassword();

            if (newPassword != confirmPassword)
            {
                Utility::setColor(Utility::COLOR_ERROR);
                std::cout << "Passwords do not match. Update cancelled.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                break;
            }

            citizen.setPassword(newPassword);
            FileManager::saveCitizens(citizens);
            Utility::setColor(Utility::COLOR_SUCCESS);
            std::cout << "Password updated successfully.\n";
            Utility::setColor(Utility::COLOR_DEFAULT);
            break;
        }
        case 5:
        default:
            return;
    }

    Utility::pauseScreen();
}

static void citizenDashboard(Citizen& citizen, std::vector<Citizen>& citizens)
{
    bool loggedIn = true;

    while (loggedIn)
    {
        Utility::clearScreen();
        Utility::setColor(Utility::COLOR_TITLE);
        std::cout << "\n===================== CITIZEN DASHBOARD =====================\n";
        Utility::setColor(Utility::COLOR_MENU);
        std::cout << "1. View Profile\n";
        std::cout << "2. Update Profile\n";
        std::cout << "3. Apply for Verification\n";
        std::cout << "4. View Verification Status\n";
        std::cout << "5. View Digital Identity Card\n";
        std::cout << "6. Logout\n";
        Utility::setColor(Utility::COLOR_DEFAULT);

        int choice = promptMenuChoice("Enter your choice: ", 1, 6);

        switch (choice)
        {
            case 1:
                Utility::clearScreen();
                citizen.displayProfile();
                Utility::pauseScreen();
                break;

            case 2:
                updateProfileMenu(citizen, citizens);
                break;

            case 3:
            {
                Utility::clearScreen();
                Utility::setColor(Utility::COLOR_TITLE);
                std::cout << "\n================= APPLY FOR VERIFICATION ====================\n";
                Utility::setColor(Utility::COLOR_DEFAULT);

                if (citizen.getVerificationStatus() == VerificationStatus::VERIFIED)
                {
                    Utility::setColor(Utility::COLOR_SUCCESS);
                    std::cout << "You are already Verified. No action needed.\n";
                    Utility::setColor(Utility::COLOR_DEFAULT);
                }
                else if (citizen.getVerificationStatus() == VerificationStatus::REJECTED)
                {
                    Utility::setColor(Utility::COLOR_ERROR);
                    std::cout << "Your application was Rejected. Please contact an administrator.\n";
                    Utility::setColor(Utility::COLOR_DEFAULT);
                }
                else
                {
                    std::vector<std::string> errors;
                    bool eligible = Verification::applyForVerification(citizen, citizens, errors);

                    if (eligible)
                    {
                        Utility::setColor(Utility::COLOR_SUCCESS);
                        std::cout << "Your data meets all verification requirements.\n";
                        std::cout << "Your application is Pending review by an administrator.\n";
                        Utility::setColor(Utility::COLOR_DEFAULT);
                    }
                    else
                    {
                        Utility::setColor(Utility::COLOR_WARNING);
                        std::cout << "Your application is Pending, but the following issues\n";
                        std::cout << "must be corrected before an administrator can verify you:\n";
                        Utility::setColor(Utility::COLOR_ERROR);
                        for (const std::string& err : errors)
                        {
                            std::cout << "  - " << err << "\n";
                        }
                        Utility::setColor(Utility::COLOR_DEFAULT);
                    }
                }

                Utility::pauseScreen();
                break;
            }

            case 4:
                Utility::clearScreen();
                Utility::setColor(Utility::COLOR_TITLE);
                std::cout << "\nVerification Status: ";
                Utility::setColor(Utility::COLOR_WARNING);
                std::cout << citizen.getVerificationStatusText() << "\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                Utility::pauseScreen();
                break;

            case 5:
                Utility::clearScreen();
                citizen.displayIDCard();
                Utility::pauseScreen();
                break;

            case 6:
                FileManager::saveCitizens(citizens);
                Utility::setColor(Utility::COLOR_SUCCESS);
                std::cout << "Logged out successfully.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                Utility::pauseScreen();
                loggedIn = false;
                break;

            default:
                break;
        }
    }
}

static void searchCitizenMenu(std::vector<Citizen>& citizens)
{
    Utility::clearScreen();
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== SEARCH CITIZEN ========================\n";
    Utility::setColor(Utility::COLOR_MENU);
    std::cout << "1. By Citizen ID\n";
    std::cout << "2. By Name\n";
    std::cout << "3. By Email\n";
    std::cout << "4. By Mobile\n";
    std::cout << "5. By Aadhaar\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    int choice = promptMenuChoice("Enter your choice: ", 1, 5);

    std::cout << "Enter search term: ";
    std::string term = Utility::readLine();

    std::vector<Citizen*> matches;

    for (Citizen& citizen : citizens)
    {
        bool isMatch = false;

        switch (choice)
        {
            case 1:
                isMatch = (toUpperCopy(citizen.getCitizenID()) == toUpperCopy(term));
                break;
            case 2:
                isMatch = (Utility::toLower(citizen.getName()).find(Utility::toLower(term)) != std::string::npos);
                break;
            case 3:
                isMatch = (Utility::toLower(citizen.getEmail()) == Utility::toLower(term));
                break;
            case 4:
                isMatch = (citizen.getMobile() == term);
                break;
            case 5:
                isMatch = (citizen.getAadhaarNumber() == term);
                break;
            default:
                break;
        }

        if (isMatch)
        {
            matches.push_back(&citizen);
        }
    }

    Utility::clearScreen();
    if (matches.empty())
    {
        Utility::setColor(Utility::COLOR_WARNING);
        std::cout << "No matching citizen found.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
    }
    else
    {
        for (Citizen* match : matches)
        {
            match->displayProfile();
        }
    }

    Utility::pauseScreen();
}

static void viewAllCitizens(const std::vector<Citizen>& citizens)
{
    Utility::clearScreen();
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== ALL CITIZENS ==========================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    if (citizens.empty())
    {
        Utility::setColor(Utility::COLOR_WARNING);
        std::cout << "No citizens registered yet.\n";
        Utility::setColor(Utility::COLOR_DEFAULT);
    }
    else
    {
        std::cout << std::left
                  << std::setw(10) << "ID"
                  << std::setw(22) << "Name"
                  << std::setw(28) << "Email"
                  << std::setw(14) << "Mobile"
                  << "Status\n";
        std::cout << "-------------------------------------------------------------\n";

        for (const Citizen& citizen : citizens)
        {
            std::cout << std::left
                      << std::setw(10) << citizen.getCitizenID()
                      << std::setw(22) << citizen.getName()
                      << std::setw(28) << citizen.getEmail()
                      << std::setw(14) << citizen.getMobile()
                      << citizen.getVerificationStatusText() << "\n";
        }
    }

    Utility::pauseScreen();
}

static void adminDashboard(std::vector<Citizen>& citizens, Admin& admin)
{
    bool loggedIn = true;

    while (loggedIn)
    {
        Utility::clearScreen();
        Utility::setColor(Utility::COLOR_TITLE);
        std::cout << "\n===================== ADMIN DASHBOARD =======================\n";
        Utility::setColor(Utility::COLOR_MENU);
        std::cout << "1. View All Citizens\n";
        std::cout << "2. Search Citizen\n";
        std::cout << "3. Verify Citizen\n";
        std::cout << "4. Reject Citizen\n";
        std::cout << "5. Delete Citizen\n";
        std::cout << "6. Reports\n";
        std::cout << "7. Export Report\n";
        std::cout << "8. Logout\n";
        Utility::setColor(Utility::COLOR_DEFAULT);

        int choice = promptMenuChoice("Enter your choice: ", 1, 8);

        switch (choice)
        {
            case 1:
                viewAllCitizens(citizens);
                break;

            case 2:
                searchCitizenMenu(citizens);
                break;

            case 3:
            {
                Utility::clearScreen();
                std::cout << "Enter Citizen ID to verify: ";
                std::string id = Utility::readLine();
                Citizen* citizen = findCitizenById(citizens, id);

                if (citizen == nullptr)
                {
                    Utility::setColor(Utility::COLOR_ERROR);
                    std::cout << "No citizen found with that ID.\n";
                    Utility::setColor(Utility::COLOR_DEFAULT);
                }
                else
                {
                    std::vector<std::string> errors;
                    bool ok = Verification::verifyCitizen(*citizen, citizens, errors);

                    if (ok)
                    {
                        FileManager::saveCitizens(citizens);
                        Utility::setColor(Utility::COLOR_SUCCESS);
                        std::cout << "Citizen " << citizen->getCitizenID() << " has been Verified.\n";
                        Utility::setColor(Utility::COLOR_DEFAULT);
                    }
                    else
                    {
                        Utility::setColor(Utility::COLOR_ERROR);
                        std::cout << "Verification failed. The following issues were found:\n";
                        for (const std::string& err : errors)
                        {
                            std::cout << "  - " << err << "\n";
                        }
                        Utility::setColor(Utility::COLOR_DEFAULT);
                    }
                }

                Utility::pauseScreen();
                break;
            }

            case 4:
            {
                Utility::clearScreen();
                std::cout << "Enter Citizen ID to reject: ";
                std::string id = Utility::readLine();
                Citizen* citizen = findCitizenById(citizens, id);

                if (citizen == nullptr)
                {
                    Utility::setColor(Utility::COLOR_ERROR);
                    std::cout << "No citizen found with that ID.\n";
                    Utility::setColor(Utility::COLOR_DEFAULT);
                }
                else
                {
                    Verification::rejectCitizen(*citizen);
                    FileManager::saveCitizens(citizens);
                    Utility::setColor(Utility::COLOR_WARNING);
                    std::cout << "Citizen " << citizen->getCitizenID() << " has been Rejected.\n";
                    Utility::setColor(Utility::COLOR_DEFAULT);
                }

                Utility::pauseScreen();
                break;
            }

            case 5:
            {
                Utility::clearScreen();
                std::cout << "Enter Citizen ID to delete: ";
                std::string id = Utility::readLine();

                auto it = std::find_if(citizens.begin(), citizens.end(),
                    [&id](const Citizen& c) { return toUpperCopy(c.getCitizenID()) == toUpperCopy(Utility::trim(id)); });

                if (it == citizens.end())
                {
                    Utility::setColor(Utility::COLOR_ERROR);
                    std::cout << "No citizen found with that ID.\n";
                    Utility::setColor(Utility::COLOR_DEFAULT);
                }
                else
                {
                    it->displayProfile();

                    if (promptYesNo("Delete this citizen?"))
                    {
                        citizens.erase(it);
                        FileManager::saveCitizens(citizens);
                        Utility::setColor(Utility::COLOR_SUCCESS);
                        std::cout << "Citizen deleted successfully.\n";
                        Utility::setColor(Utility::COLOR_DEFAULT);
                    }
                    else
                    {
                        Utility::setColor(Utility::COLOR_WARNING);
                        std::cout << "Deletion cancelled.\n";
                        Utility::setColor(Utility::COLOR_DEFAULT);
                    }
                }

                Utility::pauseScreen();
                break;
            }

            case 6:
            {
                Utility::clearScreen();
                ReportManager::ReportData report = ReportManager::generateReport(citizens);
                ReportManager::displayReport(report);
                Utility::pauseScreen();
                break;
            }

            case 7:
            {
                Utility::clearScreen();
                ReportManager::ReportData report = ReportManager::generateReport(citizens);
                bool exported = ReportManager::exportReport(report);

                if (exported)
                {
                    Utility::setColor(Utility::COLOR_SUCCESS);
                    std::cout << "Report exported successfully to " << FileManager::REPORT_FILE << "\n";
                    Utility::setColor(Utility::COLOR_DEFAULT);
                }
                else
                {
                    Utility::setColor(Utility::COLOR_ERROR);
                    std::cout << "Failed to export report.\n";
                    Utility::setColor(Utility::COLOR_DEFAULT);
                }

                Utility::pauseScreen();
                break;
            }

            case 8:
                Utility::setColor(Utility::COLOR_SUCCESS);
                std::cout << "Admin logged out successfully.\n";
                Utility::setColor(Utility::COLOR_DEFAULT);
                Utility::pauseScreen();
                loggedIn = false;
                break;

            default:
                break;
        }
    }

    (void)admin;
}

int main()
{
    std::vector<Citizen> citizens = FileManager::loadCitizens();
    Admin admin = FileManager::loadAdmin();

    printWelcomeBanner();
    Utility::pauseScreen();

    bool running = true;

    while (running)
    {
        Utility::clearScreen();
        Utility::setColor(Utility::COLOR_TITLE);
        std::cout << "\n===================== MAIN MENU =============================\n";
        Utility::setColor(Utility::COLOR_MENU);
        std::cout << "1. Citizen Registration\n";
        std::cout << "2. Citizen Login\n";
        std::cout << "3. Admin Login\n";
        std::cout << "4. Exit\n";
        Utility::setColor(Utility::COLOR_DEFAULT);

        int choice = promptMenuChoice("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1:
                Utility::clearScreen();
                Authentication::registerCitizen(citizens);
                FileManager::saveCitizens(citizens);
                Utility::pauseScreen();
                break;

            case 2:
            {
                Utility::clearScreen();
                Citizen* citizen = Authentication::loginCitizen(citizens);
                if (citizen != nullptr)
                {
                    Utility::pauseScreen();
                    citizenDashboard(*citizen, citizens);
                }
                else
                {
                    Utility::pauseScreen();
                }
                break;
            }

            case 3:
            {
                Utility::clearScreen();
                bool ok = Authentication::loginAdmin(admin);
                if (ok)
                {
                    Utility::pauseScreen();
                    adminDashboard(citizens, admin);
                }
                else
                {
                    Utility::pauseScreen();
                }
                break;
            }

            case 4:
                if (promptYesNo("Are you sure you want to exit?"))
                {
                    FileManager::saveCitizens(citizens);
                    FileManager::saveAdmin(admin);
                    running = false;
                }
                break;

            default:
                break;
        }
    }

    Utility::setColor(Utility::COLOR_SUCCESS);
    std::cout << "\nThank you for using the Smart Digital Identity Verification System.\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    return 0;
}
