#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer
{
private:
    int id;
    string name;
    string email;
    string phone;
    string status;

public:
    Customer(int, string, string, string, string);

    int getId() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    string getStatus() const;

    void setEmail(string);
    void setPhone(string);
    void setStatus(string);
};

#endif
