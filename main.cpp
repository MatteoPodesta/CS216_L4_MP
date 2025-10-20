#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;

const string INPUT_FILE = "file_in.dat";
const string OUTPUT_FILE = "file_out.dat";
const string ERROR_FILE = "file_err.dat";
const string LOG_FILE = "log_out.dat";

const double MIN_BALANCE = -50.00;

const int LIST_SIZE = 15;

const string DEFAULT_FIRSTNAME = "FirstName";
const string DEFAULT_LASTNAME = "LastName";
const string DEFAULT_EMAIL = "Username@mailserver.com";
const string DEFAULT_SSN = "0000000000";

const double DEFAULT_AVAILABLEBAL = 5.00;
const double DEFAULT_PRESENTBAL = 100.00;

class BankAccount {
public:

    BankAccount();
    BankAccount(const BankAccount& NewAccount);
    BankAccount(string SSN, string firstname, string lastname, string email);
    ~BankAccount();

    void setAccount(string newSSN, string newFirstName, string newLastName, string newEmail, int newID, double newAvailableBalance, double newPresentBalance);
    void setAccount(string newSSN, string newFirstName, string newLastName, string newEmail);

    void setEmail(string newEmail);
    void setID(int newID);
    void setName(string newFirstName, string newLastName);

    const string getFirstName() { return firstName; }
    const string getLastName() { return lastName; }
    const string getSSN() { return SSN; }
    const string getEmail() { return emailAdress; }
    const double getAvailableBalance() { return availableBalance * 1.0; }
    const double getPresentBalance() { return presentBalance * 1.0; }
    const int getAccountID() { return accountID; }
    const bool isValidAcc() { return isValid; }

    string toString();

    void substactAcc() { numOfAccounts--; }
    void AddAccount() { numOfAccounts++; }
    const int getAccNum() { return numOfAccounts; }

private:

    int accountID = 0;
    double availableBalance = DEFAULT_AVAILABLEBAL;
    double presentBalance = DEFAULT_PRESENTBAL;
    string firstName = DEFAULT_FIRSTNAME;
    string lastName = DEFAULT_LASTNAME;
    string emailAdress = DEFAULT_EMAIL;
    string SSN = DEFAULT_SSN;
    bool isValid = false;

    static int numOfAccounts;
    
};
class InvalidAccount {

public:
    InvalidAccount() { message = "Unknown Error"; }
    InvalidAccount(double value) { message = value; }
    InvalidAccount(string value) { message = value; }
    string what() { return message; }
private:

    string message = "";

};

void processAccounts(BankAccount List[], BankAccount* pList[], int& Size);
void printListToScreen(BankAccount list[], int size);
void printListToFile(BankAccount list[], int size, const string filename);
void defaultMenuOption();
void exeptionMenuOption();

int main()
{

    enum {

        PRINT = 1,
        TEST,
        QUIT

    };

    
    int input = 0;
    while (input != QUIT) {

        input = 0;
        cout << "\nMenu:\n1.Print Amount of Bank Acc Objects in Memory\n2.Test Exeption Class\n3.Quit\n\nInput: ";
        cin >> input;
        BankAccount Account;

        switch (input) {
        case PRINT:
            cout << "Amount of Accounts in Memory: " << Account.getAccNum();
            break;
        case TEST:
            exeptionMenuOption();
            break;
        case QUIT:

            break;
        default:
            defaultMenuOption();
            break;

        }

    }

    return 0;
}

BankAccount::BankAccount() {
    //these will be the default paramiters, I wasnt able to find anything that mentioned what the specifics were for the default
    setAccount(DEFAULT_SSN, DEFAULT_FIRSTNAME, DEFAULT_LASTNAME, DEFAULT_EMAIL, 0, DEFAULT_AVAILABLEBAL, DEFAULT_PRESENTBAL);

}
BankAccount::BankAccount(const BankAccount& copyFromAccount) {
    //I called it "copyFromAccount to remind myself that the 'BankAccount' you are copying from is the one being passed through the function.

    setAccount(copyFromAccount.SSN, copyFromAccount.firstName, copyFromAccount.lastName, copyFromAccount.emailAdress, copyFromAccount.accountID, copyFromAccount.availableBalance, copyFromAccount.presentBalance);
    isValid = copyFromAccount.isValid;
}
BankAccount::BankAccount(string SSN, string firstname, string lastname, string email) {

    setAccount(SSN, firstname, lastname, email, accountID, availableBalance, presentBalance);

}
BankAccount::~BankAccount() {

    setAccount(DEFAULT_SSN, DEFAULT_FIRSTNAME, DEFAULT_LASTNAME, DEFAULT_EMAIL, 0, DEFAULT_AVAILABLEBAL, DEFAULT_PRESENTBAL);
    substactAcc();

}

void BankAccount::setAccount(string newSSN, string newFirstName, string newLastName, string newEmail, int newID, double newAvailableBalance, double newPresentBalance) {

    int usernameSize = 0, mailserverSize = 0, firstNameSize = 0, lastNameSize = 0, ssnSize = 0, index = 0, requestCount = 0;
    string domain = "";
    try {

        while (newEmail[index] != '@' && index < newEmail.size()) {

            if ((newEmail[index] >= '0' && newEmail[index] <= '9') || (newEmail[index] >= 'A' && newEmail[index] <= 'Z') || (newEmail[index] >= 'a' && newEmail[index] <= 'z')) {

                usernameSize++;
            }
            index++;
        }
        while (newEmail[index] != '.' && index < newEmail.size()) {

            if ((newEmail[index] >= 'A' && newEmail[index] <= 'Z') || (newEmail[index] >= 'a' && newEmail[index] <= 'z')) {

                mailserverSize++;

            }
            index++;
        }

        for (int i = newEmail.length() - 3; i < newEmail.length(); i++) {

            if (newEmail[i] >= 'a' && newEmail[i] <= 'z') {

                domain = domain + newEmail[i];

            }

        }
        if ((usernameSize < 4) || (mailserverSize < 4) || ((domain != "edu") && (domain != "com"))) {
            
            throw(InvalidAccount(newEmail));

        }

        for (int i = 0; i < newFirstName.length(); i++) {

            if ((newFirstName[i] >= 'A' && newFirstName[i] <= 'Z') || (newFirstName[i] >= 'a' && newFirstName[i] <= 'z')) {

                firstNameSize++;

            }

        }
        if (firstNameSize < 2) {

            throw(InvalidAccount(newFirstName));

        }

        for (int i = 0; i < newLastName.length(); i++) {

            if ((newLastName[i] >= 'A' && newLastName[i] <= 'Z') || (newLastName[i] >= 'a' && newLastName[i] <= 'z')) {

                lastNameSize++;

            }

        }
        if (lastNameSize < 2) {

            throw(InvalidAccount(newLastName));

        }
        
        for (int i = 0; i < newSSN.length(); i++) {

            if (newSSN[i] >= '0' && newSSN[i] <= '9') {

                ssnSize++;

            }

        }
        if (ssnSize < 10) {

            throw(InvalidAccount(newSSN));

        }

        if (newAvailableBalance > presentBalance) {

            cout << "Available balance cannot be greater than Present Balance, cancelling request...\n";
            throw(InvalidAccount(newAvailableBalance));

        }
        else if (newAvailableBalance < MIN_BALANCE) {

            cout << "Available balance cannot be less than $50.00, cancelling request...\n";
            throw(InvalidAccount(newAvailableBalance));

        }

        if (newPresentBalance < MIN_BALANCE) {

            cout << "Present balance cannot be less than $50.00, cancelling request...\n";
            throw(InvalidAccount(newPresentBalance));

        }


        firstName = newFirstName;
        lastName = newLastName;
        accountID = newID;
        emailAdress = newEmail;
        SSN = newSSN;
        presentBalance = newPresentBalance;
        availableBalance = newAvailableBalance;

        AddAccount();
        if (isValid == false) {

            accountID = (((rand() % 1000) + 1) * 100) + (getAccNum());

            if (domain == "edu") {

                presentBalance = presentBalance + 50.00;

            }

        }
        isValid = true;
    }
    catch (InvalidAccount Error) {

        cout << "ERROR: " << Error.what() << " is Invalid, it will not be stored...\n";
        
    }
    catch(...){

        cout << "Unknown Error...\n";

    }

}
void BankAccount::setAccount(string newSSN, string newFirstName, string newLastName, string newEmail) {

    setAccount(newSSN, newFirstName, newLastName, newEmail, accountID, availableBalance, presentBalance);

}
void BankAccount::setName(string newFirstName, string newLastName) {

    setAccount(SSN, newFirstName, newLastName, emailAdress, accountID, availableBalance, presentBalance);

}

void BankAccount::setEmail(string newEmail) {

    setAccount(SSN, firstName, lastName, newEmail, accountID, availableBalance, presentBalance);

}
void BankAccount::setID(int newID) {

    setAccount(SSN, firstName, lastName, emailAdress, newID, availableBalance, presentBalance);

}

string BankAccount::toString() {

    stringstream accountString;
    accountString << left << setw(15) << SSN << setw(15) << firstName << setw(15) << lastName << setw(25) << emailAdress << right << setw(10) << accountID  << setw(20) << fixed << setprecision(2) << availableBalance << setw(20) << presentBalance << "\n";
    return accountString.str();
}

int BankAccount::numOfAccounts = 0;

void processAccounts(BankAccount List[], BankAccount* pList[], int& Size) {

    ifstream infile;

    infile.open(INPUT_FILE);

    if (!infile) {
        cout << "Cannot open file" << endl;
        exit(EXIT_FAILURE);
    }

    string tempFirstName = "", tempLastName = "", tempEmailAdress = "", tempSSN = "";
    int usernameSize = 0, mailserverSize = 0, firstNameSize = 0, lastNameSize = 0, ssnSize = 0, index = 0, requestCount = 0;
    string domain = "";


    infile >> tempSSN >> tempFirstName >> tempLastName >> tempEmailAdress;

    while (infile) {

        BankAccount tempAccount(tempSSN, tempFirstName, tempLastName, tempEmailAdress);

        if (tempAccount.isValidAcc() == true) {

            if (Size < LIST_SIZE) {

                List[Size] = tempAccount;
                pList[Size] = &List[Size];
                Size++;

            }
            if(Size >= LIST_SIZE){

                tempAccount.substactAcc();

            }
            if (tempAccount.getSSN() == DEFAULT_SSN) {

                tempAccount.substactAcc();

            }

        }
        requestCount++;
        infile >> tempSSN >> tempFirstName >> tempLastName >> tempEmailAdress;

    }

    if (Size >= LIST_SIZE) {

        cout << "Warning: Max file sized reached, some valid accounts may not be recorded\n";
        Size = LIST_SIZE;

    }

    cout << "\nRequests Processed: " << requestCount << "\nSuccsesfull Accounts: " << Size << "\nAccounts not stored: " << requestCount - (Size) << endl;

    infile.close();

}
void printListToScreen(BankAccount list[], int size) {

    if (size <= 0) {
        cout << "There are none available at the moment, make you you've processed all checking account requests\n";
    }
    else {

        for (int i = 0; i < size; i++) {

            cout << list[i].toString();

        }

    }

}
void printListToFile(BankAccount list[], int size, const string filename) {

    ofstream outfile;
    outfile.open(filename);

    if (size <= 0) {
        cout << "There are none available at the moment, make you you've processed all checking account requests\n";
    }
    else {

        for (int i = 0; i < size; i++) {

            outfile << list[i].toString();

        }

    }

    outfile.close();

}
void defaultMenuOption() {

    cout << "Invalid choice, try again\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}
void exeptionMenuOption() {

    int listSize = 0;
    BankAccount accList[LIST_SIZE];
    BankAccount* pAccList[LIST_SIZE];
    processAccounts(accList, pAccList, listSize);

    
    cout << "\nSSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance\n========================================================================================================================\n";
    printListToScreen(accList, listSize);
    

}

/*

Menu:
1.Print Amount of Bank Acc Objects in Memory
2.Test Exeption Class
3.Quit

Input: 2
ERROR: mary_leelapc.com is Invalid, it will not be stored...
ERROR: Horses@l.com is Invalid, it will not be stored...
ERROR: Milkman@lapc.ed is Invalid, it will not be stored...
ERROR: p is Invalid, it will not be stored...
ERROR: 114486951 is Invalid, it will not be stored...
ERROR: doppry@lapc.gov is Invalid, it will not be stored...
ERROR: lo@lapc.edu is Invalid, it will not be stored...

Requests Processed: 15
Succsesfull Accounts: 8
Accounts not stored: 7

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
9105758202     Pope           Percy          Perc33@lapc.com               94317                5.00              100.00
8174489654     vaons          McLame         So_Cool@lapc.edu              43718                5.00              150.00
1561652163     Vins           Venus          ilove_space@lapc.com          60519                5.00              100.00
3841968436     Dan            Phantom        ghost@lapc.com                15420                5.00              100.00
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            38321                5.00              150.00
0001896545     Alert          gru            despicableMe@lapc.com         71722                5.00              100.00
9999341862     Alberto        pollem         bug22Bug@lapc.com             71923                5.00              100.00
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          89624                5.00              100.00

Menu:
1.Print Amount of Bank Acc Objects in Memory
2.Test Exeption Class
3.Quit

Input: 1
Amount of Accounts in Memory: 25
Menu:
1.Print Amount of Bank Acc Objects in Memory
2.Test Exeption Class
3.Quit

Input: 2
ERROR: mary_leelapc.com is Invalid, it will not be stored...
ERROR: Horses@l.com is Invalid, it will not be stored...
ERROR: Milkman@lapc.ed is Invalid, it will not be stored...
ERROR: p is Invalid, it will not be stored...
ERROR: 114486951 is Invalid, it will not be stored...
ERROR: doppry@lapc.gov is Invalid, it will not be stored...
ERROR: lo@lapc.edu is Invalid, it will not be stored...

Requests Processed: 15
Succsesfull Accounts: 8
Accounts not stored: 7

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
9105758202     Pope           Percy          Perc33@lapc.com               86942                5.00              100.00
8174489654     vaons          McLame         So_Cool@lapc.edu              64543                5.00              150.00
1561652163     Vins           Venus          ilove_space@lapc.com          75844                5.00              100.00
3841968436     Dan            Phantom        ghost@lapc.com                86045                5.00              100.00
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            74246                5.00              150.00
0001896545     Alert          gru            despicableMe@lapc.com         77947                5.00              100.00
9999341862     Alberto        pollem         bug22Bug@lapc.com             31748                5.00              100.00
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com           3649                5.00              100.00

Menu:
1.Print Amount of Bank Acc Objects in Memory
2.Test Exeption Class
3.Quit

Input: 1
Amount of Accounts in Memory: 50
Menu:
1.Print Amount of Bank Acc Objects in Memory
2.Test Exeption Class
3.Quit

Input: 3

C:\Users\Matteo\source\repos\Lab #4 Bank Account with Exceptions & Static F25\x64\Debug\Lab #4 Bank Account with Exceptions & Static F25.exe (process 10056) exited with code 0.
Press any key to close this window . . .
*/