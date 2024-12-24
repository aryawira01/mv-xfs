#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include <xfsapi.h>

// Fungsi untuk mendapatkan waktu saat ini sebagai string
std::string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return std::string(buffer);
}

class CashDispenser : public ATMDevice{
	public:
		void logTransaction(const std::string &transactionType, int amount);
		void openCashDispenser();
		void closeCashDispenser();
		void cashWithdrawal(int amount);
		void cashDeposit(int amount);
};

// Fungsi untuk mencatat log transaksi
void logTransaction(const std::string &transactionType, int amount) {
    std::ofstream logFile("transaction_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << getCurrentTime() << " - " << transactionType << " - Amount: " << amount << "\n";
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}

// Fungsi untuk membuka cash dispenser menggunakan XFS API
void openCashDispenser() {
    std::cout << "Opening cash dispenser..." << std::endl;

    HSERVICE hService;
    HRESULT hResult;
    WFSRESULT *pResult = nullptr;

    hResult = WFSOpen("CashDispenser", NULL, NULL, WFS_INDEFINITE_WAIT, WFS_VERSION, WFS_VERSION, &hService);
    if (hResult != WFS_SUCCESS) {
        std::cerr << "Failed to open cash dispenser. Error: " << hResult << std::endl;
        return;
    }

    std::cout << "Cash dispenser is open." << std::endl;
    WFSClose(hService);
}

// Fungsi untuk menutup cash dispenser menggunakan XFS API
void closeCashDispenser() {
    std::cout << "Closing cash dispenser..." << std::endl;

    HSERVICE hService;
    HRESULT hResult;
    WFSRESULT *pResult = nullptr;

    hResult = WFSOpen("CashDispenser", NULL, NULL, WFS_INDEFINITE_WAIT, WFS_VERSION, WFS_VERSION, &hService);
    if (hResult != WFS_SUCCESS) {
        std::cerr << "Failed to open cash dispenser for closing. Error: " << hResult << std::endl;
        return;
    }

    WFSClose(hService);
    std::cout << "Cash dispenser is closed." << std::endl;
}

// Fungsi untuk melakukan cash withdrawal
void cashWithdrawal(int amount) {
    openCashDispenser();
    std::cout << "Dispensing cash: " << amount << " units." << std::endl;
    logTransaction("Cash Withdrawal", amount);
    closeCashDispenser();
}

// Fungsi untuk melakukan cash deposit
void cashDeposit(int amount) {
    openCashDispenser();
    std::cout << "Accepting cash deposit: " << amount << " units." << std::endl;
    logTransaction("Cash Deposit", amount);
    closeCashDispenser();
}

int main() {
    int choice;
    int amount;

    do {
        std::cout << "\nCash Dispenser Menu:" << std::endl;
        std::cout << "1. Cash Withdrawal" << std::endl;
        std::cout << "2. Cash Deposit" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            cashWithdrawal(amount);
            break;
        case 2:
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            cashDeposit(amount);
            break;
        case 3:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);

    return 0;
}

