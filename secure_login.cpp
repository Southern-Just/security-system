#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>  // For sleep
#include <termios.h> // For password masking
#include <iomanip>   // For formatting

using namespace std;

// Utility function to mask password input
string getPasswordInput() {
    string password;
    char ch;
    termios oldt, newt;

    // Turn off terminal echo
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n' && ch != EOF) {
        password += ch;
        cout << '*';  // Mask input
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << endl;
    return password;
}

// Save user credentials to file
bool saveCredentials(const string& id, const string& password) {
    ofstream file("users.txt", ios::app);
    if (!file) {
        cerr << "Error: Unable to open file for saving credentials.\n";
        return false;
    }
    file << id << ":" << password << endl;
    file.close();
    return true;
}

// Validate user credentials during login
bool validateCredentials(const string& id, const string& password) {
    ifstream file("users.txt");
    if (!file) {
        cerr << "Error: Unable to access the file for validation.\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string storedID, storedPassword;

        if (getline(ss, storedID, ':') && getline(ss, storedPassword)) {
            if (id == storedID && password == storedPassword) {
                return true;
            }
        }
    }
    return false;
}

// User registration process
void registerUser() {
    system("clear");
    cout << "\n========== User Registration ==========\n";
    string id, password;

    cout << "Enter a unique Login ID: ";
    cin >> id;

    do {
        cout << "Enter a strong password (min 8 characters): ";
        password = getPasswordInput();
        if (password.length() < 8) {
            cout << "Error: Password must be at least 8 characters.\n";
        }
    } while (password.length() < 8);

    if (saveCredentials(id, password)) {
        cout << "\nUser registered successfully!\n";
    } else {
        cout << "\nRegistration failed. Please try again.\n";
    }
    sleep(2);
}

// User login process
void loginUser() {
    system("clear");
    cout << "\n========== User Login ==========\n";
    string id, password;

    cout << "Enter your Login ID: ";
    cin >> id;

    cout << "Enter your password: ";
    password = getPasswordInput();

    if (validateCredentials(id, password)) {
        cout << "\nLogin successful! Redirecting...\n";
        sleep(2);
        system("clear");
        cout << "\nWelcome, " << id << "!\n";
    } else {
        cout << "\nError: Incorrect Login ID or Password.\n";
    }
    sleep(2);
}

// Main menu for the application
void mainMenu() {
    bool running = true;

    while (running) {
        system("clear");
        cout << "\n=========================================\n";
        cout << "         Registration & Login System\n";
        cout << "=========================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "\nGoodbye!\n";
                running = false;
                sleep(2);
                break;
            default:
                cout << "\nError: Invalid choice. Please try again.\n";
                sleep(2);
        }
    }
}

// Main function
int main() {
    mainMenu();
    return 0;
}
