#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
};

const int MAX_CONTACTS = 50;
Contact phonebook[MAX_CONTACTS];
int contactCount = 0;

void loadContactsFromFile() {
    ifstream file("contacts.txt");
    if (file.is_open()) {
        while (file >> phonebook[contactCount].name >> phonebook[contactCount].phoneNumber) {
            ++contactCount;
        }
        file.close();
    }
}

void saveContactsToFile() {
    ofstream file("contacts.txt");
    if (file.is_open()) {
        for (int i = 0; i < contactCount; ++i) {
            file << phonebook[i].name << " " << phonebook[i].phoneNumber << endl;
        }
        file.close();
    }
}

void addContact() {
    string name, phoneNumber;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    if (phoneNumber.find_first_not_of("0123456789") == string::npos) {
        phonebook[contactCount++] = { name, phoneNumber };
        cout << "Contact added successfully!" << endl;
    }
    else {
        cout << "Wrong Input" << endl;
    }
}

void updateContact() {
    string name, phoneNumber;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    if (phoneNumber.find_first_not_of("0123456789") == string::npos) {
        bool found = false;
        for (int i = 0; i < contactCount; ++i) {
            if (phonebook[i].name == name) {
                phonebook[i].phoneNumber = phoneNumber;
                cout << "Contact updated successfully!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            phonebook[contactCount++] = { name, phoneNumber };
            cout << "New contact added successfully!" << endl;
        }
    }
    else {
        cout << "Wrong Input" << endl;
    }
}

void deleteContact() {
    string name;
    cout << "Enter name: ";
    cin >> name;

    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (phonebook[i].name == name) {
            for (int j = i; j < contactCount - 1; ++j) {
                phonebook[j] = phonebook[j + 1];
            }
            --contactCount;
            cout << "Contact deleted successfully!" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Contact name is not on the system" << endl;
    }
}

void retrieveContact() {
    string keyword;
    cout << "Enter name or number: ";
    cin >> keyword;

    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (phonebook[i].name == keyword || phonebook[i].phoneNumber == keyword) {
            cout << "Name: " << phonebook[i].name << ", Phone Number: " << phonebook[i].phoneNumber << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Contact name is not on the system" << endl;
    }
}

void showAllContacts() {
    if (contactCount == 0) {
        cout << "Phonebook is empty" << endl;
    }
    else {
        cout << "All Contacts:" << endl;
        for (int i = 0; i < contactCount; ++i) {
            cout << "Name: " << phonebook[i].name << ", Phone Number: " << phonebook[i].phoneNumber << endl;
        }
    }
}

int main() {
    loadContactsFromFile();

    while (true) {
        cout << "\nPhone Book Menu:" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Update Contact" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. Retrieve Contact" << endl;
        cout << "5. Show All Data" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addContact();
            break;
        case 2:
            updateContact();
            break;
        case 3:
            deleteContact();
            break;
        case 4:
            retrieveContact();
            break;
        case 5:
            showAllContacts();
            break;
        case 6:
            saveContactsToFile();
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
