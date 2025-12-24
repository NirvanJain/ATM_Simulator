#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Function to get current date-time as string
string getDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[20];
    sprintf(buffer, "%02d-%02d-%04d %02d:%02d:%02d",
            ltm->tm_mday,
            ltm->tm_mon + 1,
            ltm->tm_year + 1900,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec);

    return string(buffer);
}

int main() {
    string username = "Akhila";
    string ipin = "5678";          // Updated default PIN
    int balance = 50000;           // Updated initial balance
    string transactions[50];       // Max 50 transactions
    int tcount = 0;
    int limit = 15000;             // Updated daily withdrawal limit
    int dailyWithdraw = 0;
    int attempts = 0;

    cout << "===========================================\n";
    cout << "             WELCOME TO ATM SYSTEM\n";
    cout << "===========================================\n\n";

    // Login
    while (attempts < 3) {
        string pin;
        cout << "Enter your 4-digit PIN: ";
        cin >> pin;

        if (pin == ipin) {
            cout << "\n-------------------------------------------\n";
            cout << "Welcome, " << username << "!\n";
            cout << "-------------------------------------------\n";
            break;
        } else {
            attempts++;
            if (attempts == 3) {
                cout << "Too many wrong attempts. Account locked.\n";
                return 0;
            } else {
                cout << "Incorrect PIN. Attempts left: " 
                     << (3 - attempts) << endl;
            }
        }
    }

    while (true) {
        int choice;
        cout << "\n===========================================\n";
        cout << "                 MAIN MENU\n";
        cout << "===========================================\n";
        cout << "1. Check Balance\n";
        cout << "2. Withdraw Cash\n";
        cout << "3. Deposit Cash\n";
        cout << "4. Change PIN\n";
        cout << "5. Mini Statement\n";
        cout << "6. Exit\n";
        cout << "===========================================\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "\n-------------------------------------------\n";
            cout << "Your current balance is ₹" << balance << endl;
            cout << "-------------------------------------------\n";
            break;

        case 2: {
            int amt;
            cout << "\nEnter amount to withdraw: ";
            cin >> amt;

            if (amt % 100 != 0) {
                cout << "\nPlease enter amount in multiples of ₹100.\n";
            } else if (amt > balance) {
                cout << "\nInsufficient balance.\n";
            } else if (dailyWithdraw + amt > limit) {
                cout << "\nDaily withdrawal limit of ₹15000 reached.\n";
            } else {
                balance -= amt;
                dailyWithdraw += amt;
                string date = getDateTime();
                transactions[tcount++] =
                    date + " -" + to_string(amt) + " Withdraw";
                cout << "\nPlease collect your cash.\n";
            }
            break;
        }

        case 3: {
            int deposit;
            cout << "\nEnter amount to deposit: ";
            cin >> deposit;

            balance += deposit;
            string date = getDateTime();
            transactions[tcount++] =
                date + " +" + to_string(deposit) + " Deposit";
            cout << "\nDeposit successful.\n";
            break;
        }

        case 4: {
            string oldPin, newPin1, newPin2;
            cout << "\nEnter current PIN: ";
            cin >> oldPin;

            if (oldPin == ipin) {
                cout << "Enter new 4-digit PIN: ";
                cin >> newPin1;
                cout << "Re-enter new PIN to confirm: ";
                cin >> newPin2;

                if (newPin1.length() == 4 && newPin1 == newPin2) {
                    ipin = newPin1;
                    cout << "\nPIN updated successfully!\n";
                } else {
                    cout << "\nPIN mismatch. Try again.\n";
                }
            } else {
                cout << "\nIncorrect current PIN!\n";
            }
            break;
        }

        case 5:
            cout << "\n-------------- Mini Statement -------------\n";
            if (tcount == 0) {
                cout << "No transactions yet.\n";
            } else {
                int start = (tcount > 5) ? tcount - 5 : 0;
                for (int i = start; i < tcount; i++) {
                    cout << transactions[i] << endl;
                }
            }
            cout << "-------------------------------------------\n";
            break;

        case 6:
            cout << "\n-------------------------------------------\n";
            cout << "Thank you for using our ATM.\n";
            cout << "Session Ended: " << getDateTime() << endl;
            cout << "-------------------------------------------\n";
            return 0;

        default:
            cout << "\nInvalid option! Please select between 1–6.\n";
        }
    }

    return 0;
}
