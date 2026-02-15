#include <iostream>
#include <fstream>
using namespace std;

class Account {
private:
    int accountNumber;
    string name;
    double balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() const {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder: " << name;
        cout << "\nBalance: ₹" << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Amount Deposited Successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
        } else {
            balance -= amount;
            cout << "Amount Withdrawn Successfully.\n";
        }
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void updateInFile() {
        fstream file("accounts.dat", ios::in | ios::out | ios::binary);
        Account acc;

        while (file.read((char*)&acc, sizeof(Account))) {
            if (acc.getAccountNumber() == accountNumber) {
                file.seekp(-sizeof(Account), ios::cur);
                file.write((char*)this, sizeof(Account));
                break;
            }
        }

        file.close();
    }

    void saveToFile() {
        ofstream file("accounts.dat", ios::binary | ios::app);
        file.write((char*)this, sizeof(Account));
        file.close();
    }

    static void displayAllAccounts() {
        ifstream file("accounts.dat", ios::binary);
        Account acc;

        while (file.read((char*)&acc, sizeof(Account))) {
            acc.showAccount();
            cout << "------------------------\n";
        }

        file.close();
    }
};

int main() {
    int choice;
    Account acc;

    do {
        cout << "\n🏦 Bank Management System\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            acc.createAccount();
            acc.saveToFile();
            break;

        case 2: {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;

            fstream file("accounts.dat", ios::in | ios::out | ios::binary);
            Account temp;

            while (file.read((char*)&temp, sizeof(Account))) {
                if (temp.getAccountNumber() == accNo) {
                    cout << "Enter Deposit Amount: ";
                    cin >> amount;
                    temp.deposit(amount);
                    file.seekp(-sizeof(Account), ios::cur);
                    file.write((char*)&temp, sizeof(Account));
                    break;
                }
            }
            file.close();
            break;
        }

        case 3: {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;

            fstream file("accounts.dat", ios::in | ios::out | ios::binary);
            Account temp;

            while (file.read((char*)&temp, sizeof(Account))) {
                if (temp.getAccountNumber() == accNo) {
                    cout << "Enter Withdraw Amount: ";
                    cin >> amount;
                    temp.withdraw(amount);
                    file.seekp(-sizeof(Account), ios::cur);
                    file.write((char*)&temp, sizeof(Account));
                    break;
                }
            }
            file.close();
            break;
        }

        case 4:
            Account::displayAllAccounts();
            break;

        case 5:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
