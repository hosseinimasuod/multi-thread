#include <iostream>
#include <mutex>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>

class BankAccount {
public:
	BankAccount();
	BankAccount(int initialBalance, const std::string& AccountName);
	void deposit(int money);
	void withdraw(int money);
	void transfer(int money, BankAccount& toAccount);
	int getBalance() const;
	std::string getAccountName() const;

private:
	int balance;
	std::string name;
	mutable std::mutex mtx; // Mutex to protect the balance
	void logTransaction(const std::string& message) const;
};