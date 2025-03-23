#include "BankAccount.hpp"


BankAccount::BankAccount() : balance(0) {}

BankAccount::BankAccount(int initialBalance) : balance(initialBalance) {}

void BankAccount::deposit(int money) {
    if (money < 0) {
        std::cerr << "Error: Cannot deposit a negative amount." << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
    balance += money;
    logTransaction("Deposited $" + std::to_string(money));
}

void BankAccount::withdraw(int money) {
    if (money < 0) {
        std::cerr << "Error: Cannot withdraw a negative amount." << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex before checking the balance
    if (balance >= money) {
        balance -= money;
        logTransaction("Withdrew $" + std::to_string(money));
    }
    else {
        std::cerr << "Error: Insufficient balance." << std::endl;
    }
}

int BankAccount::getBalance() const {
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
    return balance;
}

void BankAccount::logTransaction(const std::string& message) const {
    // Fetch the current time
    auto now = std::chrono::system_clock::now();
    // Convert the time point (now) to a time_t object
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;

    // Populate the tm structure with the current time
    if (localtime_s(&now_tm, &now_time_t)) {
        std::cerr << "Error: Failed to convert time." << std::endl;
        return;
    }

    // Open the log file in append mode
    std::ofstream logFile("transactions.log", std::ios::app);
    if (logFile.is_open()) {
        // Write the log entry with a timestamp
        logFile << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S")
            << " - " << message << " (Balance: $" << balance << ")" << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open log file." << std::endl;
    }
}