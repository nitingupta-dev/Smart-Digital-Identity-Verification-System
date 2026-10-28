#pragma once

#include "Citizen.h"
#include <string>

class Admin : public Citizen
{
private:
    std::string username;

public:
    Admin();

    Admin(const std::string& username, const std::string& password);

    ~Admin() override;

    std::string getUsername() const;

    bool verifyCredentials(const std::string& inputUsername,
                            const std::string& inputPassword) const;

    void displayProfile() const override;

    static Admin createDefaultAdmin();
};
