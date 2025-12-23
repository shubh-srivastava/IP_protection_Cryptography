#include <iostream>
#include "blockchain.h"

int main() {
    srand(time(nullptr));

    Blockchain bc;

    int choice;
    std::string user, content;

    while (true) {
        std::cout << "\n1. Register User\n"
                  << "2. Create Block\n"
                  << "3. Verify Ownership\n"
                  << "4. View Blockchain\n"
                  << "5. Exit\n";

        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::cout << "User ID: ";
            std::cin >> user;
            if (bc.registerUser(user))
                std::cout << "User registered.\n";
            else
                std::cout << "User already exists.\n";
        }
        else if (choice == 2) {
            std::cout << "User ID: ";
            std::cin >> user;
            std::cin.ignore();
            std::cout << "Content: ";
            getline(std::cin, content);
            bc.createBlock(user, content);
        }
        else if (choice == 3) {
            std::cout << "User ID: ";
            std::cin >> user;
            std::cin.ignore();
            std::cout << "Content: ";
            getline(std::cin, content);
            bc.verifyOwnership(user, content);
        }
        else if (choice == 4) {
            bc.viewChain();
        }
        else {
            break;
        }
    }

    return 0;
}
