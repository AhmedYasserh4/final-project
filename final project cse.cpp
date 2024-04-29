#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// structure to represent a contact
struct Contact {
    string name;
    string phoneNumber;
};

const int MAX_CONTACTS = 100;
Contact phonebook[MAX_CONTACTS];
int contactCount = 0;

// function to load contacts from file
void loadContactsFromFile() {
    ifstream file("contacts.txt");
    if (file.is_open()) {
        while (file >> phonebook[contactCount].name >> phonebook[contactCount].phoneNumber) {
            ++contactCount;
        }
        file.close();
    }
}

// function to save contacts to file
void saveContactsToFile() {
    ofstream file("contacts.txt");
    if (file.is_open()) {
        for (int i = 0; i < contactCount; ++i) {
            file << phonebook[i].name << " " << phonebook[i].phoneNumber << endl;
        }
        file.close();
    }
}

// function to add a contact to the phonebook
void addContact() {
    string name, phoneNumber;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

// check if phone number contains only digits
    if (phoneNumber.find_first_not_of("0123456789") == string::npos) {
        phonebook[contactCount++] = { name, phoneNumber };
        cout << "Contact added successfully!" << endl;
    }
    else {
        cout << "Wrong Input" << endl;
    }
}

// function to update or add a contact in the phonebook
void updateContact() {
    string name, phoneNumber;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

// check if phone number contains only digits
    if (phoneNumber.find_first_not_of("0123456789") == string::npos) {
        bool found = false;
        for (int i = 0; i < contactCount; ++i) {
            if (phonebook[i].name == name) {
// Update existing contact
                phonebook[i].phoneNumber = phoneNumber;
                cout << "Contact updated successfully!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
// Add new contact
            phonebook[contactCount++] = { name, phoneNumber };
            cout << "New contact added successfully!" << endl;
        }
    }
    else {
        cout << "Wrong Input" << endl;
    }
}

// Function to delete a contact from the phonebook
void deleteContact() {
    string name;
    cout << "Enter name: ";
    cin >> name;

    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (phonebook[i].name == name) {
// Delete contact
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

// Function to retrieve a contact from the phonebook
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

// Function to show all contacts in the phonebook
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