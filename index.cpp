#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct User {
    string name;
    string password;
    int age;
};

// Function prototypes
void registerUser();
bool loginUser();
void changePassword();

// Global variables
vector<User> users;

int main() {
    int choice;
    cout << "Southern-Just Security\n";
    cout << "__________________\n\n";
    cout << "|              1.Register            |\n";
    cout << "|              2.Login               |\n";
    cout << "|              3.Change password     |\n";
    cout << "|              4.End program         |\n\n";

    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if(loginUser()) {
                    cout << "Login successful!\n";
                    // Proceed with logged in user's tasks
                } else {
                    cout << "Login failed. Incorrect credentials.\n";
                }
                break;
            case 3:
                changePassword();
                break;
            case 4:
                cout << "Thank you!\n";
                break;
            default:
                cout << "Enter a valid choice.\n";
        }
    } while(choice != 4);

    return 0;
}

void registerUser() {
    User newUser;
    cout << "Register\n";
    cout << "Enter username: ";
    cin >> newUser.name;
    cout << "Enter password: ";
    cin >> newUser.password;
    cout << "Enter age: ";
    cin >> newUser.age;

    // Add user to the vector
    users.push_back(newUser);

    cout << "Registration successful.\n";
}

bool loginUser() {
    string username, password;
    cout << "Login\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Search for user in the vector
    for(const auto& user : users) {
        if(user.name == username && user.password == password) {
            return true;
        }
    }
    return false;
}

void changePassword() {
    string username, oldPassword, newPassword;
    cout << "Change password\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter old password: ";
    cin >> oldPassword;
    
    // Search for user in the vector
    for(auto& user : users) {
        if(user.name == username && user.password == oldPassword) {
            cout << "Enter new password: ";
            cin >> newPassword;
            user.password = newPassword;
            cout << "Password changed successfully.\n";
            return;
        }
    }
    cout << "User not found or incorrect password.\n";
}
