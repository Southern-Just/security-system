#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>   // for sleep
#include <termios.h>  // for password masking
#include <iomanip>    // for formatting
#include <string>
#include <vector>

using namespace std;

class Login {
private:
    string loginID, password;
public:
    void setCredentials(const string& id, const string& pw) {
        loginID = id;
        password = pw;
    }

    string getID() const {
        return loginID;
    }

    string getPW() const {
        return password;
    }
};

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

// Helper functions for file operations
bool saveCredentials(const string& id, const string& pw) {
    ofstream outfile("Login.txt", ios::app);
    if (!outfile) {
        cerr << "\n\tError: Unable to open file for saving credentials.\n";
        return false;
    }
    outfile << id << ":" << pw << endl;
    outfile.close();
    return true;
}

bool validateCredentials(const string& id, const string& pw) {
    ifstream infile("Login.txt");
    if (!infile) {
        cerr << "\n\tError: Unable to open file for reading credentials.\n";
        return false;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string storedID, storedPW;
        char delimiter;

        ss >> storedID >> delimiter >> storedPW;
        if (id == storedID && pw == storedPW) {
            return true;
        }
    }
    return false;
}

// Registration Function
void registration() {
    system("clear");
    cout << "\n\t========== User Registration ==========\n";
    string id, pw;

    cout << "\tEnter Login ID: ";
    cin >> id;

    do {
        cout << "\tEnter Password (min 8 characters): ";
        pw = getPasswordInput();
        if (pw.length() < 8) {
            cout << "\tError: Password must be at least 8 characters.\n";
        }
    } while (pw.length() < 8);

    if (saveCredentials(id, pw)) {
        cout << "\n\tUser registered successfully!\n";
    }
    sleep(2);
}

// Login Function
void login() {
    system("clear");
    cout << "\n\t========== User Login ==========\n";
    string id, pw;

    cout << "\tEnter Login ID: ";
    cin >> id;

    cout << "\tEnter Password: ";
    pw = getPasswordInput();

    if (validateCredentials(id, pw)) {
        cout << "\n\tLogin successful! Redirecting...\n";
        sleep(2);
        system("clear");
        cout << "\n\tWelcome to your dashboard!\n";
    } else {
        cout << "\n\tError: Incorrect Login ID or Password.\n";
        sleep(2);
    }
}

// Main Menu
void mainMenu() {
    bool running = true;

    while (running) {
        system("clear");
        cout << "\n\t=========================================\n";
        cout << "\t         Registration & Login System\n";
        cout << "\t=========================================\n";
        cout << "\t1. Register\n";
        cout << "\t2. Login\n";
        cout << "\t3. Exit\n";
        cout << "\t=========================================\n";
        cout << "\tEnter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                registration();
                break;
            case 2:
                login();
                break;
            case 3:
                system("clear");
                cout << "\n\tGoodbye!\n";
                running = false;
                sleep(2);
                break;
            default:
                cout << "\n\tError: Invalid choice. Please try again.\n";
                sleep(2);
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
