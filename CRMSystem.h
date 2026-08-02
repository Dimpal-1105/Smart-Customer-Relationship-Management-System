#ifndef CRMSYSTEM_H
#define CRMSYSTEM_H

#include <vector>
#include <string>
#include "Customer.h"

using namespace std;

class CRMSystem
{
private:
    vector<Customer> customers;
    int nextId;

    void loadFromFile();
    void saveToFile();

public:
    CRMSystem();

    bool login();

    void addCustomer(string name, string email, string phone, string status);
    void viewAllCustomers();
    void searchCustomer(int id);
    void deleteCustomer(int id);

    bool customerExists(int id);

    void modifyCustomer(int id, string newEmail, string newPhone, string newStatus);
    void modifyCustomerEmail(int id, string newEmail);
    void modifyCustomerPhone(int id, string newPhone);
    void modifyCustomerStatus(int id, string newStatus);

    void showSmartDashboard();

    void clearConsole();

    bool isValidPhone(string phone);
    bool isValidEmailPrefix(string prefix);

    void showMenu();
};

#endif
