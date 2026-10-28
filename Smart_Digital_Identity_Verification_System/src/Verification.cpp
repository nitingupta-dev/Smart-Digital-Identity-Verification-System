#include "Verification.h"
#include "Utility.h"

bool Verification::isAadhaarUnique(const Citizen& citizen, const std::vector<Citizen>& allCitizens)
{
    for (const Citizen& other : allCitizens)
    {
        if (other.getCitizenID() != citizen.getCitizenID() &&
            other.getAadhaarNumber() == citizen.getAadhaarNumber())
        {
            return false;
        }
    }
    return true;
}

bool Verification::isEmailUnique(const Citizen& citizen, const std::vector<Citizen>& allCitizens)
{
    std::string target = Utility::toLower(citizen.getEmail());
    for (const Citizen& other : allCitizens)
    {
        if (other.getCitizenID() != citizen.getCitizenID() &&
            Utility::toLower(other.getEmail()) == target)
        {
            return false;
        }
    }
    return true;
}

bool Verification::isMobileUnique(const Citizen& citizen, const std::vector<Citizen>& allCitizens)
{
    for (const Citizen& other : allCitizens)
    {
        if (other.getCitizenID() != citizen.getCitizenID() &&
            other.getMobile() == citizen.getMobile())
        {
            return false;
        }
    }
    return true;
}

bool Verification::validateCitizenData(const Citizen& citizen,
                                        const std::vector<Citizen>& allCitizens,
                                        std::vector<std::string>& errors)
{
    errors.clear();

    if (!Utility::isValidAadhaar(citizen.getAadhaarNumber()))
    {
        errors.push_back("Aadhaar number must contain exactly 12 digits.");
    }
    else if (!isAadhaarUnique(citizen, allCitizens))
    {
        errors.push_back("Aadhaar number is already used by another citizen.");
    }

    if (!Utility::isValidMobile(citizen.getMobile()))
    {
        errors.push_back("Mobile number must contain exactly 10 digits.");
    }
    else if (!isMobileUnique(citizen, allCitizens))
    {
        errors.push_back("Mobile number is already used by another citizen.");
    }

    if (!Utility::isValidEmail(citizen.getEmail()))
    {
        errors.push_back("Email address format is invalid.");
    }
    else if (!isEmailUnique(citizen, allCitizens))
    {
        errors.push_back("Email address is already used by another citizen.");
    }

    if (!Utility::isValidAge(citizen.getAge()))
    {
        errors.push_back("Citizen must be at least 18 years old.");
    }

    return errors.empty();
}

bool Verification::applyForVerification(const Citizen& citizen,
                                         const std::vector<Citizen>& allCitizens,
                                         std::vector<std::string>& errors)
{
    return validateCitizenData(citizen, allCitizens, errors);
}

bool Verification::verifyCitizen(Citizen& citizen,
                                  const std::vector<Citizen>& allCitizens,
                                  std::vector<std::string>& errors)
{
    if (!validateCitizenData(citizen, allCitizens, errors))
    {
        return false;
    }

    citizen.setVerificationStatus(VerificationStatus::VERIFIED);
    return true;
}

void Verification::rejectCitizen(Citizen& citizen)
{
    citizen.setVerificationStatus(VerificationStatus::REJECTED);
}
