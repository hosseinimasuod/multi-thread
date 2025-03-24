#include "BankAccount.hpp"


BankAccount::BankAccount() : balance(0), name("Unknown") {}

BankAccount::BankAccount(int initialBalance, const std::string& AccountName) : balance(initialBalance), name(AccountName) {}

void BankAccount::deposit(int money) {
    if (money < 0) {
        std::cerr << "Error: Cannot deposit a negative amount." << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
    balance += money;
    logTransaction("Deposited $" + std::to_string(money) + " into " + name);
}

void BankAccount::withdraw(int money) {
    if (money < 0) {
        std::cerr << "Error: Cannot withdraw a negative amount." << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex before checking the balance
    if (balance >= money) {
        balance -= money;
        logTransaction("Withdrew $" + std::to_string(money) + " from " + name);
    }
    else {
        std::cerr << "Error: Insufficient balance." << std::endl;
    }
}

void BankAccount::transfer(int money, BankAccount& toAccount) {
   if (money < 0) {
        std::cerr << "Error: Cannot transfer a negative amount." << std::endl;
        return;
    }
   // Lock both accounts to avoid deadlock
   std::unique_lock<std::mutex> lock1(mtx, std::defer_lock);
   std::unique_lock<std::mutex> lock2(toAccount.mtx, std::defer_lock);
   std::lock(lock1, lock2); // Lock both mutexes safely

   if (balance >= money) {
       balance -= money;
       toAccount.balance += money;
       logTransaction("Transferred $" + std::to_string(money) + " from " + name + " to " + toAccount.getAccountName());
   }
   else {
       std::cerr << "Error: Insufficient balance in " << name << " for transfer." << std::endl;
   }
}

int BankAccount::getBalance() const {
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
    return balance;
}

std::string BankAccount::getAccountName() const {
    return name;
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