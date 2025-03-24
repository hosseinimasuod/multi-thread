#include <iostream>
#include <thread>
#include "BankAccount.hpp"

//using namespace std;

#define NoDepostTask 30
#define NoWithdrawTask 20
#define NoTransferTask 10

void depositTask(BankAccount& bnkacc, int amount){
    for (int i = 0; i < NoDepostTask; ++i) {
        bnkacc.deposit(amount);
        //cout << "Deposit thread" << endl;
    }
}

void withdrawTask(BankAccount& bnkacc, int amount) {
    for (int i = 0; i < NoWithdrawTask; ++i) {
        bnkacc.withdraw(amount);
        //cout << "Withdraw thread" << endl;
    }
}

void transferTask(BankAccount& fromAccount, BankAccount& toAccount, int amount) {
    for (int i = 0; i < NoTransferTask; ++i) {
        fromAccount.transfer(amount, toAccount);
    }
}

int main()
{
    BankAccount account1(1000, "Ali");
    BankAccount account2(2500, "Amir");

    std::thread t1(depositTask, std::ref(account1), 10);
    std::thread t2(withdrawTask, std::ref(account1), 10);
    std::thread t3(transferTask, std::ref(account1), std::ref(account2), 20);


    t1.join();
    t2.join();
    t3.join();

    std::cout << "Final balance of " << account1.getAccountName() <<" is $" << account1.getBalance() << std::endl;
    std::cout << "Final balance of " << account2.getAccountName() <<" is $" << account2.getBalance() << std::endl;

    
    return 0;
}

