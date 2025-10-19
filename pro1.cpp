#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const double INTEREST_RATE = 0.01; 
const int DAILY_WITHDRAW_LIMIT = 50000;

string current_time() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string s(dt);
    s.pop_back(); 
    return s;
}

void log_transaction(const string& name, int acc_number, const string& type, int amount) {
    ofstream trans("transactions.txt", ios::app);
    trans << current_time() << " | " << name << " | Acc#: " << acc_number
          << " | " << type << " | Amount: " << amount << endl;
    trans.close();
}

void open_account() {
    cin.ignore();
    cout << "Enter Account Name: ";
    string name;
    getline(cin, name);

    int balance = 0;
    int acc_number = 1;
    string pin;

    cout << "Set a 4-digit PIN: ";
    cin >> pin;

    ifstream infile("accounts.txt");
    string line;
    while (getline(infile, line)) acc_number++;
    infile.close();

    ofstream out("accounts.txt", ios::app);
    out << name << " " << acc_number << " " << balance << " " << pin << endl;
    out.close();

    cout << "\nAccount created successfully!\n";
    cout << "Name: " << name << "\nAccount Number: " << acc_number
         << "\nBalance: " << balance << endl;
}

bool verify_pin(int acc_number) {
    string input_pin;
    cout << "Enter PIN: ";
    cin >> input_pin;

    ifstream file("accounts.txt");
    string name, pin;
    int number, balance;
    while (file >> name >> number >> balance >> pin) {
        if (number == acc_number) {
            return input_pin == pin;
        }
    }
    return false;
}

void search_user() {
    int op;
    cout << "1: Search with Account Name\n2: Search with Account Number\nChoice: ";
    cin >> op;

    cin.ignore();
    string search_name;
    int search_acc = -1;

    if (op == 1) {
        cout << "Enter Account Name to search: ";
        getline(cin, search_name);
    } else {
        cout << "Enter Account Number to search: ";
        cin >> search_acc;
    }

    ifstream file("accounts.txt");
    if (!file) { cout << "File not found.\n"; return; }

    string name, pin;
    int number, balance;
    bool found = false;

    while (file >> name >> number >> balance >> pin) {
        if ((op == 1 && name == search_name) || (op == 2 && number == search_acc)) {
            cout << "\nAccount found:\nName: " << name
                 << "\nAccount Number: " << number
                 << "\nBalance: " << balance << endl;
            found = true;
            break;
        }
    }

    if (!found) cout << "No account found.\n";
    file.close();
}

void check_balance() {
    int acc;
    cout << "Enter Account Number to check balance: ";
    cin >> acc;

    if (!verify_pin(acc)) { cout << "Incorrect PIN.\n"; return; }

    ifstream file("accounts.txt");
    string name, pin;
    int number, balance;
    bool found = false;

    while (file >> name >> number >> balance >> pin) {
        if (number == acc) {
            balance += balance * INTEREST_RATE;
            cout << "\nAccount Balance for " << name << " (Acc#: " << number << ") is " << balance << endl;
            found = true;
            break;
        }
    }

    if (!found) cout << "Account not found.\n";
    file.close();
}

void deposit() {
    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    if (!verify_pin(acc)) { cout << "Incorrect PIN.\n"; return; }

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");
    string name, pin;
    int number, balance;
    bool found = false;

    while (file >> name >> number >> balance >> pin) {
        if (number == acc) {
            int amount;
            do {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                if (amount <= 0) cout << "Amount must be positive.\n";
            } while (amount <= 0);

            balance += amount;
            cout << "Deposit successful. New Balance: " << balance << endl;
            log_transaction(name, number, "Deposit", amount);
            found = true;
        }
        temp << name << " " << number << " " << balance << " " << pin << endl;
    }

    file.close(); temp.close();
    remove("accounts.txt"); rename("temp.txt", "accounts.txt");

    if (!found) cout << "Account not found.\n";
}

void withdraw() {
    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    if (!verify_pin(acc)) { cout << "Incorrect PIN.\n"; return; }

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");
    string name, pin;
    int number, balance;
    bool found = false;
    int daily_total = 0;

    while (file >> name >> number >> balance >> pin) {
        if (number == acc) {
            int amount;
            while (true) {
                cout << "Enter amount to withdraw: ";
                cin >> amount;

                if (amount <= 0) cout << "Amount must be positive.\n";
                else if (amount > balance) { cout << "Insufficient Balance.\n"; break; }
                else if (daily_total + amount > DAILY_WITHDRAW_LIMIT) { cout << "Daily withdrawal limit exceeded.\n"; break; }
                else {
                    balance -= amount; daily_total += amount;
                    cout << "Withdrawal successful. New Balance: " << balance << endl;
                    log_transaction(name, number, "Withdraw", amount);
                    break;
                }
            }
            found = true;
        }
        temp << name << " " << number << " " << balance << " " << pin << endl;
    }

    file.close(); temp.close();
    remove("accounts.txt"); rename("temp.txt", "accounts.txt");

    if (!found) cout << "Account not found.\n";
}

void delete_account() {
    int acc;
    cout << "Enter Account Number to delete: ";
    cin >> acc;

    if (!verify_pin(acc)) { cout << "Incorrect PIN.\n"; return; }

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");
    string name, pin;
    int number, balance;
    bool found = false;

    while (file >> name >> number >> balance >> pin) {
        if (number == acc) { cout << "Account deleted successfully.\n"; found = true; continue; }
        temp << name << " " << number << " " << balance << " " << pin << endl;
    }

    file.close(); temp.close();
    remove("accounts.txt"); rename("temp.txt", "accounts.txt");

    if (!found) cout << "Account not found.\n";
}

void fund_transfer() {
    cout << "Enter Your Account Number: ";
    int source_acc;
    cin >> source_acc;

    if (!verify_pin(source_acc)) { cout << "Incorrect PIN.\n"; return; }

    ifstream file("accounts.txt");
    if (!file) { cout << "File not found.\n"; return; }

    string name, pin;
    int number, balance;
    int dest_acc, amount;
    bool found_source = false, found_dest = false;

    cout << "\nAvailable Accounts:\n";
    while (file >> name >> number >> balance >> pin) {
        if (number != source_acc)
            cout << "Name: " << name << " | Account Number: " << number << " | Balance: " << balance << endl;
    }
    file.clear();
    file.seekg(0);

    cout << "Enter Destination Account Number: ";
    cin >> dest_acc;

    ofstream temp("temp.txt");
    while (file >> name >> number >> balance >> pin) {
        if (number == source_acc) {
            found_source = true;
            cout << "Source Account: " << name << " | Balance: " << balance << endl;
            do {
                cout << "Enter Amount to Transfer: ";
                cin >> amount;
                if (amount <= 0) cout << "Amount must be positive.\n";
                else if (amount > balance) cout << "Insufficient Balance.\n";
            } while (amount <= 0 || amount > balance);
            balance -= amount;
            log_transaction(name, number, "Transfer Sent", amount);
        } else if (number == dest_acc) {
            found_dest = true;
            cout << "Destination Account: " << name << " | Balance: " << balance << endl;
            balance += amount;
            log_transaction(name, number, "Transfer Received", amount);
        }
        temp << name << " " << number << " " << balance << " " << pin << endl;
    }

    file.close();
    temp.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found_source) cout << "Source account not found.\n";
    if (!found_dest) cout << "Destination account not found.\n";
    if (found_source && found_dest) cout << "Transfer successful.\n";
}

int main() {
    int choice;
    while (true) {
        system("cls");
        cout << "\nWelcome to the CYBERex Bank System!!\n   Mohsan Razaq Creation\n";
        cout << "===============================\n";
        cout << "1: Open Account\n2: Check Balance\n3: Deposit\n4: Withdraw\n5: Check Account Details\n6: Fund Transfer\n7: Delete Account\n8: Quit\n";
        cout << "Select An Option To Proceed: ";
        cin >> choice;

        switch (choice) {
            case 1: open_account(); break;
            case 2: check_balance(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: search_user(); break;
            case 6: fund_transfer(); break;
            case 7: delete_account(); break;
            case 8: cout << "Exiting... Goodbye!\n"; return 0;
            default: cout << "Invalid option, try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
