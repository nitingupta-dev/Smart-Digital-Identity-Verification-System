#include "Citizen.h"
#include "Utility.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <vector>

static const size_t CITIZEN_RECORD_FIELD_COUNT = 14;

Citizen::Citizen()
    : Person(), citizenID(""), aadhaarNumber(""), registrationDate(""),
      verificationStatus(VerificationStatus::PENDING)
{
}

Citizen::Citizen(const std::string& citizenID,
                 const std::string& name,
                 int age,
                 const std::string& gender,
                 const std::string& dateOfBirth,
                 const std::string& mobile,
                 const std::string& email,
                 const std::string& address,
                 const std::string& password,
                 const std::string& securityQuestion,
                 const std::string& securityAnswer,
                 const std::string& aadhaarNumber,
                 const std::string& registrationDate)
    : Person(name, age, gender, dateOfBirth, mobile, email, address,
             password, securityQuestion, securityAnswer),
      citizenID(citizenID), aadhaarNumber(aadhaarNumber),
      registrationDate(registrationDate),
      verificationStatus(VerificationStatus::PENDING)
{
}

Citizen::Citizen(const std::string& citizenID,
                 const std::string& name,
                 int age,
                 const std::string& gender,
                 const std::string& dateOfBirth,
                 const std::string& mobile,
                 const std::string& email,
                 const std::string& address,
                 const std::string& password,
                 const std::string& securityQuestion,
                 const std::string& securityAnswer,
                 const std::string& aadhaarNumber,
                 const std::string& registrationDate,
                 VerificationStatus verificationStatus)
    : Person(name, age, gender, dateOfBirth, mobile, email, address,
             password, securityQuestion, securityAnswer),
      citizenID(citizenID), aadhaarNumber(aadhaarNumber),
      registrationDate(registrationDate),
      verificationStatus(verificationStatus)
{
}

Citizen::~Citizen()
{
}

std::string Citizen::getCitizenID() const
{
    return citizenID;
}

std::string Citizen::getAadhaarNumber() const
{
    return aadhaarNumber;
}

std::string Citizen::getRegistrationDate() const
{
    return registrationDate;
}

VerificationStatus Citizen::getVerificationStatus() const
{
    return verificationStatus;
}

std::string Citizen::getVerificationStatusText() const
{
    return verificationStatusToString(verificationStatus);
}

void Citizen::setVerificationStatus(VerificationStatus status)
{
    verificationStatus = status;
}

void Citizen::displayProfile() const
{
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================== CITIZEN PROFILE =====================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::cout << std::left << std::setw(22) << "Citizen ID"          << ": " << citizenID << "\n";
    std::cout << std::left << std::setw(22) << "Name"                << ": " << name << "\n";
    std::cout << std::left << std::setw(22) << "Age"                 << ": " << age << "\n";
    std::cout << std::left << std::setw(22) << "Gender"              << ": " << gender << "\n";
    std::cout << std::left << std::setw(22) << "Date of Birth"       << ": " << dateOfBirth << "\n";
    std::cout << std::left << std::setw(22) << "Mobile"              << ": " << mobile << "\n";
    std::cout << std::left << std::setw(22) << "Email"               << ": " << email << "\n";
    std::cout << std::left << std::setw(22) << "Aadhaar (Masked)"    << ": " << Utility::maskAadhaar(aadhaarNumber) << "\n";
    std::cout << std::left << std::setw(22) << "Address"             << ": " << address << "\n";
    std::cout << std::left << std::setw(22) << "Registration Date"   << ": " << registrationDate << "\n";

    Utility::setColor(Utility::COLOR_WARNING);
    std::cout << std::left << std::setw(22) << "Verification Status" << ": " << getVerificationStatusText() << "\n";
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "=============================================================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);
}

void Citizen::displayIDCard() const
{
    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "\n===================================\n";
    std::cout << "           DIGITAL ID CARD          \n";
    std::cout << "===================================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);

    std::cout << "Citizen ID          : " << citizenID << "\n";
    std::cout << "Name                : " << name << "\n";
    std::cout << "Date of Birth       : " << dateOfBirth << "\n";
    std::cout << "Aadhaar (Masked)    : " << Utility::maskAadhaar(aadhaarNumber) << "\n";
    std::cout << "Registration Date   : " << registrationDate << "\n";
    std::cout << "Verification Status : " << getVerificationStatusText() << "\n";

    Utility::setColor(Utility::COLOR_TITLE);
    std::cout << "===================================\n";
    Utility::setColor(Utility::COLOR_DEFAULT);
}

std::string Citizen::toFileRecord() const
{
    std::ostringstream oss;
    oss << citizenID << "|"
        << name << "|"
        << age << "|"
        << gender << "|"
        << dateOfBirth << "|"
        << mobile << "|"
        << email << "|"
        << address << "|"
        << password << "|"
        << securityQuestion << "|"
        << securityAnswer << "|"
        << aadhaarNumber << "|"
        << registrationDate << "|"
        << verificationStatusToString(verificationStatus);

    return oss.str();
}

Citizen Citizen::fromFileRecord(const std::string& line)
{
    std::vector<std::string> fields = Utility::splitString(line, '|');

    if (fields.size() != CITIZEN_RECORD_FIELD_COUNT)
    {
        throw std::runtime_error("Malformed citizen record: incorrect field count");
    }

    int parsedAge = 0;
    try
    {
        parsedAge = std::stoi(fields[2]);
    }
    catch (const std::exception&)
    {
        throw std::runtime_error("Malformed citizen record: invalid age value");
    }

    VerificationStatus status = verificationStatusFromString(fields[13]);

    return Citizen(
        fields[0],
        fields[1],
        parsedAge,
        fields[3],
        fields[4],
        fields[5],
        fields[6],
        fields[7],
        fields[8],
        fields[9],
        fields[10],
        fields[11],
        fields[12],
        status);
}

std::string Citizen::generateCitizenID(int serialNumber)
{
    std::ostringstream oss;
    oss << "CIT" << std::setfill('0') << std::setw(4) << serialNumber;
    return oss.str();
}

std::string Citizen::verificationStatusToString(VerificationStatus status)
{
    switch (status)
    {
        case VerificationStatus::VERIFIED:
            return "Verified";
        case VerificationStatus::REJECTED:
            return "Rejected";
        case VerificationStatus::PENDING:
        default:
            return "Pending";
    }
}

VerificationStatus Citizen::verificationStatusFromString(const std::string& text)
{
    std::string lowered = Utility::toLower(text);

    if (lowered == "verified")
    {
        return VerificationStatus::VERIFIED;
    }
    if (lowered == "rejected")
    {
        return VerificationStatus::REJECTED;
    }

    return VerificationStatus::PENDING;
}
