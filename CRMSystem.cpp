#include "CRMSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>

using namespace std;

void CRMSystem::showMenu()
{
    clearConsole();
    cout<<"========================"<<endl;
    cout<<"  SMART CRM SYSTEM "<<endl;
    cout<<"========================"<<endl;
    cout<<"1. Add New Customer"<<endl;
    cout<<"2. View All Customers"<<endl;
    cout<<"3. Search Customer by ID"<<endl;
    cout<<"4. Modify Customer"<<endl;
    cout<<"5. Delete Customer"<<endl;
    cout<<"6. Smart Analytics Dashboard"<<endl;
    cout<<"7. Exit System"<<endl;
    cout<<"========================"<<endl;
    cout<<"Enter your choice (1-7): ";
}

bool CRMSystem::isValidPhone(string phone)
{
    if(phone.length()!=10)
        return false;

    for(char c : phone)
    {
        if(!isdigit(c))
            return false;
    }

    return true;
}

bool CRMSystem::isValidEmailPrefix(string prefix)
{
    if(prefix.length()<3 || prefix.length()>30)
        return false;

    for(char c : prefix)
    {
        if(!islower(c) && !isdigit(c))
            return false;
    }

    return true;
}

CRMSystem::CRMSystem()
{
    nextId = 1;
    loadFromFile();
}

void CRMSystem::addCustomer(string name, string email, string phone, string status)
{
    Customer newCustomer(nextId++, name, email, phone, status);

    customers.push_back(newCustomer);
    saveToFile();

    cout<<"\nCustomer added successfully with ID: "
        <<newCustomer.getId()<<endl;
}

void CRMSystem::viewAllCustomers()
{
    if(customers.empty())
    {
        cout<<"\nNo customers currently in the system."<<endl;
        return;
    }

    cout<<"\n======================================================================"<<endl;
    cout<<left
        <<setw(5)<<"ID"
        <<setw(20)<<"Name"
        <<setw(30)<<"Email"
        <<setw(15)<<"Phone"
        <<setw(10)<<"Status"<<endl;

    cout<<"======================================================================"<<endl;

    for(auto &c : customers)
    {
        cout<<left
            <<setw(5)<<c.getId()
            <<setw(20)<<c.getName()
            <<setw(30)<<c.getEmail()
            <<setw(15)<<c.getPhone()
            <<setw(10)<<c.getStatus()
            <<endl;
    }

    cout<<"========================================================================="<<endl;
}

void CRMSystem::searchCustomer(int id)
{
    for(auto &c : customers)
    {
        if(c.getId()==id)
        {
            cout<<"\nCustomer Found"<<endl;
            cout<<"ID: "<<c.getId()<<endl;
            cout<<"Name: "<<c.getName()<<endl;
            cout<<"Email: "<<c.getEmail()<<endl;
            cout<<"Phone: "<<c.getPhone()<<endl;
            cout<<"Status: "<<c.getStatus()<<endl;
            return;
        }
    }

    cout<<"\nCustomer with ID "<<id<<" not found."<<endl;
}

bool CRMSystem::customerExists(int id)
{
    for(auto &c : customers)
    {
        if(c.getId()==id)
            return true;
    }

    return false;
}

void CRMSystem::modifyCustomer(int id,
                               string newEmail,
                               string newPhone,
                               string newStatus)
{
    for(auto &c : customers)
    {
        if(c.getId()==id)
        {
            c.setEmail(newEmail);
            c.setPhone(newPhone);
            c.setStatus(newStatus);

            saveToFile();

            cout<<"\nCustomer ID "
                <<id
                <<" updated successfully."
                <<endl;

            return;
        }
    }
}

void CRMSystem::modifyCustomerEmail(int id, string newEmail)
{
    for(auto &c : customers)
    {
        if(c.getId()==id)
        {
            c.setEmail(newEmail);

            saveToFile();

            cout<<"\nCustomer ID "
                <<id
                <<" email updated successfully."
                <<endl;

            return;
        }
    }
}

void CRMSystem::modifyCustomerPhone(int id, string newPhone)
{
    for(auto &c : customers)
    {
        if(c.getId()==id)
        {
            c.setPhone(newPhone);

            saveToFile();

            cout<<"\nCustomer ID "
                <<id
                <<" phone updated successfully."
                <<endl;

            return;
        }
    }
}

void CRMSystem::modifyCustomerStatus(int id, string newStatus)
{
    for(auto &c : customers)
    {
        if(c.getId()==id)
        {
            c.setStatus(newStatus);

            saveToFile();

            cout<<"\nCustomer ID "
                <<id
                <<" status updated to "
                <<newStatus
                <<"."<<endl;

            return;
        }
    }
}

void CRMSystem::deleteCustomer(int id)
{
    for(auto it = customers.begin(); it != customers.end(); ++it)
    {
        if(it->getId()==id)
        {
            customers.erase(it);

            saveToFile();

            cout<<"\nCustomer ID "
                <<id
                <<" deleted successfully."
                <<endl;

            return;
        }
    }

    cout<<"\nCustomer with ID "
        <<id
        <<" not found."
        <<endl;
}
void CRMSystem::showSmartDashboard()
{
    if(customers.empty())
    {
        cout<<"\nNot enough data to generate Analytics Dashboard."<<endl;
        return;
    }

    int total = customers.size();
    int leads = 0, active = 0, vip = 0;

    for(auto &c : customers)
    {
        if(c.getStatus() == "Lead")
            leads++;
        else if(c.getStatus() == "Active")
            active++;
        else if(c.getStatus() == "VIP")
            vip++;
    }

    double leadPct = ((double)leads / total) * 100;
    double activePct = ((double)active / total) * 100;
    double vipPct = ((double)vip / total) * 100;

    cout << "\n=============================================" << endl;
    cout << "          SMART BUSINESS DASHBOARD           " << endl;
    cout << "=============================================" << endl;
    cout << "Total Customers in Database: " << total << endl;
    cout << "---------------------------------------------" << endl;
    cout << left << setw(15) << "Category"
         << setw(10) << "Count"
         << "Percentage" << endl;
    cout << "---------------------------------------------" << endl;

    cout << left << setw(15) << "Leads (New)"
         << setw(10) << leads
         << fixed << setprecision(1)
         << leadPct << "%" << endl;

    cout << left << setw(15) << "Active Clients"
         << setw(10) << active
         << activePct << "%" << endl;

    cout << left << setw(15) << "VIP Clients"
         << setw(10) << vip
         << vipPct << "%" << endl;

    cout << "=============================================" << endl;

    if(leads > active)
    {
        cout << ">> INSIGHT: You have many Leads. Focus on converting them to Active clients!" << endl;
    }
    else if(vip > 0)
    {
        cout << ">> INSIGHT: Excellent job maintaining VIP relationships." << endl;
    }
}

void CRMSystem::loadFromFile()
{
    ifstream file("customers.txt");

    if(!file.is_open())
        return;

    string line;
    int maxId = 0;

    while(getline(file, line))
    {
        stringstream ss(line);

        string idStr, name, email, phone, status;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, status, ',');

        if(!idStr.empty())
        {
            try
            {
                int id = stoi(idStr);

                Customer c(id, name, email, phone, status);
                customers.push_back(c);

                if(id > maxId)
                    maxId = id;
            }
            catch(...)
            {
            }
        }
    }

    file.close();
    nextId = maxId + 1;
}

void CRMSystem::saveToFile()
{
    ofstream file("customers.txt", ios::trunc);

    for(auto &c : customers)
    {
        file << c.getId() << ","
             << c.getName() << ","
             << c.getEmail() << ","
             << c.getPhone() << ","
             << c.getStatus() << "\n";
    }

    file.close();
}

void CRMSystem::clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool CRMSystem::login()
{
    string username;
    string password;
    int attempts = 3;

    while(attempts > 0)
    {
        clearConsole();

        cout << "=========================================" << endl;
        cout << "      SMART CRM - SECURITY GATEWAY       " << endl;
        cout << "=========================================" << endl;

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if(username == "admin" && password == "admin123")
        {
            cout << "\nAccess Granted! Welcome to Smart CRM." << endl;
            cout << "Press Enter to continue...";
            cin.get();
            return true;
        }
        else
        {
            attempts--;

            cout << "\nInvalid Credentials. Attempts remaining: "
                 << attempts << endl;

            if(attempts > 0)
            {
                cout << "Press Enter to try again...";
                cin.get();
            }
        }
    }

    cout << "\nToo many failed attempts. System locking down." << endl;
    return false;
}
