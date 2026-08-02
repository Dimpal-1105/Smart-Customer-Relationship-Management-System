#include "Customer.h"

Customer::Customer(int Id, string Name, string Email, string Phone, string Status)
{
    id = Id;
    name = Name;
    email = Email;
    phone = Phone;
    status = Status;
}

int Customer::getId() const
{
    return id;
}

string Customer::getName() const
{
    return name;
}

string Customer::getEmail() const
{
    return email;
}

string Customer::getPhone() const
{
    return phone;
}

string Customer::getStatus() const
{
    return status;
}

void Customer::setEmail(string newEmail)
{
    email = newEmail;
}

void Customer::setPhone(string newPhone)
{
    phone = newPhone;
}

void Customer::setStatus(string newStatus)
{
    status = newStatus;
}
