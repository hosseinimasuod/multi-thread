#include <iostream>
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
}

void BankAccount::withdraw(int money) {
	if (money < 0) {
		std::cerr << "Error: Cannot withdraw a negative amount." << std::endl;
		return;
	}
	if (balance >= money) {
		std::lock_guard<std::mutex> lock(mtx); 
		balance -= money;
	}
	else {
		std::cerr << "Error: Insufficient balance." << std::endl;
	}
}

int BankAccount::getBalance() const {
	std::lock_guard<std::mutex> lock(mtx); 
	return balance;
}