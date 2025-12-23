#include <iostream>
#include "blockchain.h"

using namespace std;

int main() {
    srand(time(nullptr));

    Blockchain bc;

    int choice;
     string user, content;

    while (true) {
        cout << "\n1. Register User\n"
                  << "2. Create Block\n"
                  << "3. Verify Ownership\n"
                  << "4. View Blockchain\n"
                  << "5. Exit\n";

        cin >> choice;
         cin.ignore();

        if (choice == 1) {
            cout << "User ID: ";
            cin >> user;
            if(bc.registerUser(user)){
                cout << "User registered.\n";
            }
            else{
                cout << "User already exists.\n";
            }
        }
        else if(choice == 2){
            cout << "User ID: ";
            cin >> user;
            cin.ignore();
            cout << "Content: ";
            getline( cin, content);
            bc.createBlock(user, content);
        }
        else if (choice == 3){
            cout << "User ID: ";
            cin >> user;
            cin.ignore();
            cout << "Content: ";
            getline( cin, content);
            bc.verifyOwnership(user, content);
        }
        else if (choice == 4){
            bc.viewChain();
        }
        else{
            break;
        }
    }

    return 0;
}
