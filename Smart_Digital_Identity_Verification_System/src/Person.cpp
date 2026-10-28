#include "Person.h"
#include "Utility.h"

Person::Person()
    : name(""), age(0), gender(""), dateOfBirth(""), mobile(""),
      email(""), address(""), password(""), securityQuestion(""),
      securityAnswer("")
{
}

Person::Person(const std::string& name,
               int age,
               const std::string& gender,
               const std::string& dateOfBirth,
               const std::string& mobile,
               const std::string& email,
               const std::string& address,
               const std::string& password,
               const std::string& securityQuestion,
               const std::string& securityAnswer)
    : name(name), age(age), gender(gender), dateOfBirth(dateOfBirth),
      mobile(mobile), email(email), address(address), password(password),
      securityQuestion(securityQuestion), securityAnswer(securityAnswer)
{
}

Person::~Person()
{
}

std::string Person::getName() const
{
    return name;
}

int Person::getAge() const
{
    return age;
}

std::string Person::getGender() const
{
    return gender;
}

std::string Person::getDateOfBirth() const
{
    return dateOfBirth;
}

std::string Person::getMobile() const
{
    return mobile;
}

std::string Person::getEmail() const
{
    return email;
}

std::string Person::getAddress() const
{
    return address;
}

std::string Person::getPassword() const
{
    return password;
}

std::string Person::getSecurityQuestion() const
{
    return securityQuestion;
}

std::string Person::getSecurityAnswer() const
{
    return securityAnswer;
}

void Person::setMobile(const std::string& newMobile)
{
    mobile = newMobile;
}

void Person::setEmail(const std::string& newEmail)
{
    email = newEmail;
}

void Person::setAddress(const std::string& newAddress)
{
    address = newAddress;
}

void Person::setPassword(const std::string& newPassword)
{
    password = newPassword;
}

void Person::setSecurityQuestion(const std::string& question)
{
    securityQuestion = question;
}

void Person::setSecurityAnswer(const std::string& answer)
{
    securityAnswer = answer;
}

bool Person::verifyPassword(const std::string& candidatePassword) const
{
    return password == candidatePassword;
}

bool Person::verifySecurityAnswer(const std::string& candidateAnswer) const
{
    return Utility::toLower(securityAnswer) == Utility::toLower(candidateAnswer);
}
