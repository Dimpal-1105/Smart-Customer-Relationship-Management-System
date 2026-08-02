#include <iostream>
#include "CRMSystem.h"

using namespace std;

int main()
{
    CRMSystem crm;
    int choice;
    string name, email, phone, status;
    int id;
    string prefix;
    int modChoice;

    while (true)
    {
        crm.showMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
        }

        cin.ignore(10000, '\n');

        switch (choice)
        {
        case 1:
            cout << "\n  Add Customer " << endl;

            cout << "Enter Name: ";
            getline(cin, name);

            while (true)
            {
                cout << "Enter Email Prefix (3-30 lowercase letters/numbers): ";
                getline(cin, prefix);

                if (crm.isValidEmailPrefix(prefix))
                {
                    email = prefix + "@gmail.com";
                    break;
                }
                else
                {
                    cout << "Invalid prefix. Must be 3-30 characters, lowercase letters and numbers only.\n" << endl;
                }
            }

            while (true)
            {
                cout << "Enter Phone (exactly 10 digits): ";
                getline(cin, phone);

                if (crm.isValidPhone(phone))
                {
                    break;
                }
                else
                {
                    cout << "Invalid phone number. Must be exactly 10 digits.\n" << endl;
                }
            }

            int statChoice;
            cout << "Select Status:\n1. Lead\n2. Active\n3. VIP\nChoice: ";
            cin >> statChoice;

            if (statChoice == 2)
                status = "Active";
            else if (statChoice == 3)
                status = "VIP";
            else
                status = "Lead";

            cin.ignore(10000, '\n');

            crm.addCustomer(name, email, phone, status);
            break;

        case 2:
            crm.viewAllCustomers();
            break;

        case 3:
            cout << "\nEnter Customer ID to search: ";
            cin >> id;
            cin.ignore(10000, '\n');

            crm.searchCustomer(id);
            break;

        case 4:
            cout << "\nEnter Customer ID to modify: ";
            cin >> id;
            cin.ignore(10000, '\n');

            if (crm.customerExists(id))
            {
                cout << "\nWhat would you like to modify?" << endl;
                cout << "1. Modify Email only" << endl;
                cout << "2. Modify Phone only" << endl;
                cout << "3. Modify Status" << endl;
                cout << "Enter choice (1-3): ";

                cin >> modChoice;

                if (cin.fail())
                {
                    cin.clear();
                }

                cin.ignore(10000, '\n');

                if (modChoice == 1)
                {
                    cout << "Enter New Email Prefix: ";
                    getline(cin, prefix);

                    email = prefix + "@gmail.com";

                    cout << "Auto-generated New Email: " << email << endl;

                    crm.modifyCustomerEmail(id, email);
                }
                else if (modChoice == 2)
                {
                    while (true)
                    {
                        cout << "Enter New Phone (exactly 10 digits): ";
                        getline(cin, phone);

                        if (crm.isValidPhone(phone))
                        {
                            break;
                        }
                        else
                        {
                            cout << "Invalid phone number. Must be exactly 10 digits.\n" << endl;
                        }
                    }

                    crm.modifyCustomerPhone(id, phone);
                }
                else if (modChoice == 3)
                {
                    int statChoice;

                    cout << "Select New Status:\n1. Lead\n2. Active\n3. VIP\nChoice: ";
                    cin >> statChoice;

                    if (statChoice == 2)
                        status = "Active";
                    else if (statChoice == 3)
                        status = "VIP";
                    else
                        status = "Lead";

                    cin.ignore(10000, '\n');

                    crm.modifyCustomerStatus(id, status);
                }
                else
                {
                    cout << "\nInvalid choice. Returning to menu." << endl;
                }
            }
            else
            {
                cout << "\nCustomer with ID " << id << " not found." << endl;
            }

            break;

        case 5:
            cout << "\nEnter Customer ID to delete: ";
            cin >> id;
            cin.ignore(10000, '\n');

            crm.deleteCustomer(id);
            break;

        case 6:
            crm.showSmartDashboard();
            break;

        case 7:
            cout << "\nExiting Smart CRM System. Goodbye!" << endl;
            return 0;

        default:
            cout << "\nInvalid choice. Please select an option from 1 to 7." << endl;
        }

        if (choice >= 1 && choice <= 6)
        {
            cout << "\nPress Enter to return to the main menu...";
            cin.get();
        }
    }

    return 0;
}
