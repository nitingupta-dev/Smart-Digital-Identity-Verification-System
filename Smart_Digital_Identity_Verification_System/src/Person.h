#pragma once

#include <string>

class Person
{
protected:
    std::string name;
    int         age;
    std::string gender;
    std::string dateOfBirth;
    std::string mobile;
    std::string email;
    std::string address;
    std::string password;
    std::string securityQuestion;
    std::string securityAnswer;

public:
    Person();

    Person(const std::string& name,
           int age,
           const std::string& gender,
           const std::string& dateOfBirth,
           const std::string& mobile,
           const std::string& email,
           const std::string& address,
           const std::string& password,
           const std::string& securityQuestion,
           const std::string& securityAnswer);

    virtual ~Person();

    std::string getName() const;
    int         getAge() const;
    std::string getGender() const;
    std::string getDateOfBirth() const;
    std::string getMobile() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getPassword() const;
    std::string getSecurityQuestion() const;
    std::string getSecurityAnswer() const;

    void setMobile(const std::string& mobile);
    void setEmail(const std::string& email);
    void setAddress(const std::string& address);
    void setPassword(const std::string& password);
    void setSecurityQuestion(const std::string& question);
    void setSecurityAnswer(const std::string& answer);

    bool verifyPassword(const std::string& candidatePassword) const;

    bool verifySecurityAnswer(const std::string& candidateAnswer) const;

    virtual void displayProfile() const = 0;
};
