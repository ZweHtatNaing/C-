#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// ENCAPSULATION — ACCESS SPECIFIERS, GETTERS & SETTERS
//
// Encapsulation hides the internal data and only exposes
// what is necessary through controlled methods.
//
// public    — accessible from anywhere
// private   — accessible only within the class
// protected — accessible within the class and subclasses
// ─────────────────────────────────────────────────────────

class BankAccount {
private:
    // Private data — cannot be accessed directly from outside the class
    string ownerName;
    double balance;
    string pin;

public:
    // Constructor — initialise the account
    BankAccount(string name, double initialBalance, string accountPin) {
        ownerName = name;
        balance   = initialBalance;
        pin       = accountPin;
    }

    // GETTER — read-only access to private data
    string getOwnerName() { return ownerName; }
    double getBalance()   { return balance; }

    // SETTER — controlled write access with validation
    void setOwnerName(string name) {
        if (!name.empty()) {
            ownerName = name; // only update if name is not empty
        } else {
            cout << "Error: name cannot be empty." << endl;
        }
    }

    // Deposit — validates before modifying balance
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Error: deposit amount must be positive." << endl;
            return;
        }
        balance += amount;
        cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
    }

    // Withdraw — validates pin and sufficient funds
    void withdraw(double amount, string enteredPin) {
        if (enteredPin != pin) {
            cout << "Error: incorrect PIN." << endl;
            return;
        }
        if (amount > balance) {
            cout << "Error: insufficient funds." << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
    }
};

int main() {
    BankAccount account("Alice", 1000.0, "1234");

    cout << "Owner:   " << account.getOwnerName() << endl;
    cout << "Balance: $" << account.getBalance() << endl;

    // account.balance = 9999; // ERROR — balance is private, can't access directly

    cout << "\n--- Transactions ---" << endl;
    account.deposit(500.0);
    account.withdraw(200.0, "0000"); // wrong PIN
    account.withdraw(200.0, "1234"); // correct PIN
    account.deposit(-50);            // invalid amount

    cout << "\n--- Update name ---" << endl;
    account.setOwnerName("Alice Smith");
    cout << "Updated name: " << account.getOwnerName() << endl;
    account.setOwnerName(""); // invalid — triggers error

    return 0;
}
