#include <iostream>
#include <mutex>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>

class BankAccount {
public:
	BankAccount();
	BankAccount(int initialBalance);
	void deposit(int money);
	void withdraw(int money);
	int getBalance() const;
private:
	int balance;
	mutable std::mutex mtx; // Mutex to protect the balance
	void logTransaction(const std::string& message) const;
};