#pragma once

#include "Person.h"
#include <string>

enum class VerificationStatus
{
    PENDING,
    VERIFIED,
    REJECTED
};

class Citizen : public Person
{
protected:
    std::string        citizenID;
    std::string        aadhaarNumber;
    std::string        registrationDate;
    VerificationStatus verificationStatus;

public:
    Citizen();

    Citizen(const std::string& citizenID,
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
            const std::string& registrationDate);

    Citizen(const std::string& citizenID,
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
            VerificationStatus verificationStatus);

    ~Citizen() override;

    std::string        getCitizenID() const;
    std::string        getAadhaarNumber() const;
    std::string        getRegistrationDate() const;
    VerificationStatus getVerificationStatus() const;
    std::string        getVerificationStatusText() const;

    void setVerificationStatus(VerificationStatus status);

    void displayProfile() const override;

    void displayIDCard() const;

    std::string toFileRecord() const;

    static Citizen fromFileRecord(const std::string& line);

    static std::string generateCitizenID(int serialNumber);

    static std::string verificationStatusToString(VerificationStatus status);

    static VerificationStatus verificationStatusFromString(const std::string& text);
};
