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

bool isPhoneNumber(string str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void addContact() {
    string name, phoneNumber;

    cout << "Enter name: ";
    cin >> name;

    cout << "Enter phone number: ";
    cin >> phoneNumber;

    if (!isPhoneNumber(phoneNumber)) {
        cout << "Wrong Input\n";
        return;
    }

    phonebook[contactCount++] = { name, phoneNumber };
    cout << "Contact added successfully.\n";
}

void updateContact() {
    string name, phoneNumber;

    cout << "Enter name to update: ";
    cin >> name;

    cout << "Enter new phone number: ";
    cin >> phoneNumber;

    if (!isPhoneNumber(phoneNumber)) {
        cout << "Wrong Input\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (phonebook[i].name == name) {
            phonebook[i].phoneNumber = phoneNumber;
            found = true;
            cout << "Contact updated successfully.\n";
            break;
        }
    }

    if (!found) {
        phonebook[contactCount++] = { name, phoneNumber };
        cout << "Contact not found, added as new contact.\n";
    }
}

void deleteContact() {
    string name;

    cout << "Enter name to delete: ";
    cin >> name;

    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (phonebook[i].name == name) {
            for (int j = i; j < contactCount - 1; ++j) {
                phonebook[j] = phonebook[j + 1];
            }
            --contactCount;
            found = true;
            cout << "Contact deleted successfully.\n";
            break;
        }
    }
    if (!found) {
        cout << "Contact name is not on the system.\n";
    }
}

void retrieveContact() {
    string keyword;

    cout << "Enter name or phone number to search: ";
    cin >> keyword;

    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (phonebook[i].name == keyword || phonebook[i].phoneNumber == keyword) {
            cout << "Contact found: " << phonebook[i].name << " " << phonebook[i].phoneNumber << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Contact not found.\n";
    }
}

void showAllContacts() {
    cout << "All contacts:\n";
    if (contactCount == 0) {
        cout << "Phonebook is empty.\n";
    }
    else {
        for (int i = 0; i < contactCount; ++i) {
            cout << phonebook[i].name << " " << phonebook[i].phoneNumber << endl;
        }
    }
}

int main() {
    loadContactsFromFile();

    while (true)
    {
        cout << "\nChoose an operation (add | update | retrieve | delete | show | exit): ";
        string choice;
        cin >> choice;

        if (choice == "ADD" || choice == "add")
            addContact();
        else if (choice == "UPDATE" || choice == "update")
            updateContact();
        else if (choice == "RETRIEVE" || choice == "retrieve")
            retrieveContact();
        else if (choice == "DELETE" || choice == "delete")
            deleteContact();
        else if (choice == "SHOW" || choice == "show") {
            showAllContacts();
            saveContactsToFile();
            return 0;
        }
        else if (choice == "EXIT" || choice == "exit") {
            saveContactsToFile();
            return 0;
        }
        else
            cout << "Invalid choice. Please try again.\n";
    }

    return 0;
}
