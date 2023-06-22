#include <iostream>
#include "Contact.h"


// if the program gives an error comment system("clear") in main.cpp and Contact.cpp

int main() {
    ContactManager contactManager;

    int choice;
    while (true) {
        contactManager.displayMenu();
        std::cin >> choice;
        std::cin.ignore();
        
        // system("cls") --> system("clear") for unix based OS and system("cls") for windows(clear works for windows too)
        system("clear");
        // system("cls");

        if (!(choice >= 0 && choice <= 6)) {
            std::cout << "\nInvalid choice!\nPlease try again.\n\n";
            continue;
        }

        switch (choice) {
            case 1: {
                contactManager.saveContact();
                break;
            }

            case 2: {
                contactManager.displayAllContacts();
                break;
            }

            case 3: {
                contactManager.searchContact();
                break;
            }

            case 4: {
                contactManager.modifyContact();
                break;
            }

            case 5: {
                contactManager.deleteContact();
                break;
            }

            case 6: {
                contactManager.deleteAllContacts();
                break;
            }

            case 0: {
                std::cout << "Exiting...\n";
                return 0;
            }

            // default: {
            //     std::cout << "\nInvalid choice!\nPlease try again.\n";
            //     break;
            // }
        }
    }



    return 0;
}
