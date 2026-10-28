#pragma once

#include "Citizen.h"
#include <vector>
#include <string>

class Verification
{
public:
    static bool validateCitizenData(const Citizen& citizen,
                                     const std::vector<Citizen>& allCitizens,
                                     std::vector<std::string>& errors);

    static bool applyForVerification(const Citizen& citizen,
                                      const std::vector<Citizen>& allCitizens,
                                      std::vector<std::string>& errors);

    static bool verifyCitizen(Citizen& citizen,
                               const std::vector<Citizen>& allCitizens,
                               std::vector<std::string>& errors);

    static void rejectCitizen(Citizen& citizen);

private:
    static bool isAadhaarUnique(const Citizen& citizen, const std::vector<Citizen>& allCitizens);
    static bool isEmailUnique(const Citizen& citizen, const std::vector<Citizen>& allCitizens);
    static bool isMobileUnique(const Citizen& citizen, const std::vector<Citizen>& allCitizens);
};
