#include <iostream>
#include <cstring>
#include "Contact.h"

std::ifstream ContactManager::readFile() {
    std::ifstream file("contacts.txt");
    if (!file.is_open()) {
        std::cout << "Failed to open the file!\n";
    }
    return file;
}

// if the program gives an error comment system("clear") in main.cpp and Contact.cpp
void ContactManager::writeFile(const std::string& line) {
    system("clear");

    file.open("contacts.txt", std::ios::app);
    if (file.is_open()) {
        file << line << "\n";
        std::cout << "Contact added successfully.\n";
    } else {
        std::cout << "Failed to open the file!\n";
    }
    file.close();
}

void ContactManager::removeFile() {
    if (std::remove("contacts.txt") == 0) {
        std::cout << "All contacts deleted successfully.\n";
    } else {
        std::cout << "Error deleting contacts.\n";
    }
}

void ContactManager::displayMenu() {
    std::cout << "\n.................................\n";
    std::cout << ":\t Contact Manager \t:\n";
    std::cout << ".................................\n\n";
    std::cout << "1. Save new contact\n";
    std::cout << "2. Display all saved contacts\n";
    std::cout << "3. Search specific contact\n";
    std::cout << "4. Modify existing contact\n";
    std::cout << "5. Delete specific contact\n";
    std::cout << "6. Delete all existing contacts\n";
    std::cout << "0. Exit\n";
    std::cout << "\n- Enter your choice: ";
}

void ContactManager::saveContact() {
    Contact contact;
    system("clear"); // system("cls") --> system("clear") for unix based OS and system("cls") for windows(clear works for windows too)
    
    std::cout << "Enter contact name: ";
    std::getline(std::cin, contact.name);
    if (contact.name == "") {
        std::remove("temp.txt");
        std::cout << "Name is required.";
        return;
    }

    std::cout << "Enter contact last name: ";
    std::getline(std::cin, contact.lastName);

    if (contact.lastName == "") {
        std::remove("temp.txt");
        std::cout << "Last name is required.";
        return;
    }

    if (file.is_open()) {
        std::ifstream file = readFile();
        std::string tempLine;
        std::string contactFullName;

        std::getline(file, tempLine);
        contactFullName = tempLine.substr(0, tempLine.find(","));
        file.close();

        if (contactFullName == contact.name + ' ' + contact.lastName) {
            std::remove("temp.txt");
            std::cout << "There is a contact with the same name and last name!";
            return;
        }
    }

    std::cout << "Enter contact phone number: ";
    std::getline(std::cin, contact.phone);

    if (contact.phone == "") {
        std::remove("temp.txt");
        std::cout << "Phone number is required.";
        return;
    }

    for (int i = 0; contact.phone[i] != '\0'; i++) {
        if (!isdigit(contact.phone[i])) {
            std::remove("temp.txt");
            std::cout << "Phone number is invalid!";
            return;
        }
    }

    std::cout << "Enter contact email: ";
    std::getline(std::cin, contact.email);

    std::cout << "Enter Address: ";
    std::getline(std::cin, contact.address);
    
    std::string line = contact.name + " " + contact.lastName + "," + contact.phone + "," + contact.email + "," + contact.address;

    writeFile(line);
}

void ContactManager::displayAllContacts() {
    std::ifstream file = readFile();
    if (file.is_open()) {
        Contact contacts[1000];
        int contactCount = 0;

        std::string line;
        while (std::getline(file, line)) {
            int delimiter1 = line.find(",");
            int delimiter2 = line.find(",", delimiter1 + 1);
            int delimiter3 = line.find(",", delimiter2 + 1);

            contacts[contactCount].name = line.substr(0, delimiter1);
            contacts[contactCount].phone = line.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1);
            contacts[contactCount].email = line.substr(delimiter2 + 1, delimiter3 - delimiter2 - 1);
            contacts[contactCount].address = line.substr(delimiter3 + 1);

            ++contactCount;
        }

        file.close();

        for (int i = 0; i < contactCount - 1; ++i) {
            for (int j = i + 1; j < contactCount; ++j) {
                if (contacts[j].name < contacts[i].name) {
                    std::swap(contacts[i], contacts[j]);
                }
            }
        }

        for (int i = 0; i < contactCount; ++i) {
            std::cout << "\nContact " << i + 1 << ":\n";
            std::cout << "Name: " << contacts[i].name << "\n";
            std::cout << "Phone: " << contacts[i].phone << "\n";
            std::cout << "Email: " << contacts[i].email << "\n";
            std::cout << "Address: " << contacts[i].address << "\n";
        }

        if (contactCount == 0) {
            std::cout << "No contacts found.\n";
        }
    }
}

void ContactManager::searchContact() {
    std::string keyword;
    std::cout << "Enter the keyword to search: ";
    std::getline(std::cin, keyword);
    
    std::ifstream file = readFile();
    if (file.is_open()) {
        std::string line;
        bool contactFound = false;
        while (std::getline(file, line)) {
            int spaceIndex = line.find(" ");
            if (spaceIndex != std::string::npos) {
                std::string name = line.substr(0, spaceIndex);
                std::string remaining = line.substr(spaceIndex + 1);
                
                int commaIndex = remaining.find(",");
                std::string lastName = remaining.substr(0, commaIndex);
                std::string remaining2 = remaining.substr(commaIndex + 1);
                
                int commaIndex2 = remaining2.find(",");
                std::string phoneNumber = remaining2.substr(0, commaIndex2);
                
                if (name == keyword || lastName == keyword || name + " " + lastName == keyword || phoneNumber == keyword) {
                    std::cout << "\nContact found:\n";
                    std::cout << line << "\n";
                    contactFound = true;
                }
            }
        }
        if (!contactFound) {
            std::cout << "Contact not found.\n";
        }
    }
    file.close();
}

void ContactManager::modifyContact() {
    std::string keyword;
    std::cout << "Enter the keyword (full name or phone number) of the contact to modify: ";
    std::getline(std::cin, keyword);

    std::ifstream file = readFile();
    std::ofstream temp("temp.txt");
    if (file.is_open() && temp.is_open()) {
        std::string line;
        bool contactFound = false;

        while (std::getline(file, line)) {
            std::string name = line.substr(0, line.find(","));
            std::string phone = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);

            if (name == keyword || phone == keyword) {
                std::string newName, newLastName, newPhone, newEmail, newAddress;

                std::cout << "Enter new contact name: ";
                std::getline(std::cin, newName);
                if (newName.empty()) {
                    std::remove("temp.txt");
                    std::cout << "Name is required.\n";
                    return;
                }

                std::cout << "Enter new contact last name: ";
                std::getline(std::cin, newLastName);
                if (newLastName.empty()) {
                    std::remove("temp.txt");
                    std::cout << "Last name is required.\n";
                    return;
                }

                std::cout << "Enter new contact phone number: ";
                std::getline(std::cin, newPhone);
                if (newPhone.empty()) {
                    std::remove("temp.txt");
                    std::cout << "Phone number is required.\n";
                    return;
                }

                for (char c : newPhone) {
                    if (!isdigit(c)) {
                        std::remove("temp.txt");
                        std::cout << "Phone number is invalid!\n";
                        return;
                    }
                }

                std::cout << "Enter new contact email: ";
                std::getline(std::cin, newEmail);

                std::cout << "Enter new Address: ";
                std::getline(std::cin, newAddress);

                std::cout << "Are you sure you want to apply the changes? (y/n):";
                char confirmation;
                std::cin >> confirmation;
                if (confirmation != 'y') {
                    std::remove("temp.txt");
                    return;
                }
                
                line = newName + " " + newLastName + "," + newPhone + "," + newEmail + "," + newAddress;
                std::cout << "Contact modified successfully.\n";
                contactFound = true;
            }
            temp << line << "\n";
        }
        if (!contactFound) {
            std::cout << "Contact not found.\n";
        }
    } else {
        std::cout << "Failed to open the file!\n";
    }
    file.close();
    temp.close();
    std::remove("contacts.txt");
    std::rename("temp.txt", "contacts.txt");
}

void ContactManager::deleteContact() {
    std::string keyword;
    std::cout << "Enter the keyword (full name or phone number) of the contact to delete: ";
    std::getline(std::cin, keyword);

    std::ifstream file = readFile();
    std::ofstream temp("temp.txt");
    bool contactFound = false;

    if (file.is_open() && temp.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::string contactName = line.substr(0, line.find(","));
            std::string contactPhone = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);

            if (contactName == keyword || contactPhone == keyword) {
                contactFound = true;
                continue;   
            }
            temp << line << "\n";
        }
        if (!contactFound) {
            std::cout << "Contact not found.\n";
            return;
        }
    } else {
        std::cout << "Failed to open the file!\n";
        return;
    }
    file.close();
    temp.close();

    if (contactFound == false) {
        std::cout << "Contact not found.\n";
        std::remove("temp.txt");
        return;
    }

    char confirmation;
    std::cout << "Are you sure you want to delete the contact? (y/n): ";
    std::cin >> confirmation;
    if (confirmation == 'y') {
        std::remove("contacts.txt");
        std::rename("temp.txt", "contacts.txt");
        std::cout << "Contact deleted successfully.\n";
        return;
    }

    std::remove("temp.txt");
    std::cout << "Deletion canceled.\n";
}

void ContactManager::deleteAllContacts() {
    char confirmation;
    std::cout << "Are you sure you want to delete all contacts? (y/n): ";
    std::cin >> confirmation;
    if (confirmation == 'y') {
        removeFile();
        return;
    }
    std::cout << "Deletion canceled.\n";
}
