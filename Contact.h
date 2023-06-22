#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <fstream>

struct Contact {
    std::string name;
    std::string lastName;
    std::string phone;
    std::string email;
    std::string address;
};

class ContactManager {
public:
    void displayMenu();
    void saveContact();
    void displayAllContacts();
    void searchContact();
    void modifyContact();
    void deleteContact();
    void deleteAllContacts();

private:
    std::ofstream file;
    std::ifstream readFile();
    void writeFile(const std::string& line);
    void removeFile();
};

#endif
