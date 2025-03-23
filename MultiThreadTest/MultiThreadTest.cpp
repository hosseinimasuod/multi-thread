#include <iostream>
#include <thread>
#include "BankAccount.hpp"

//using namespace std;

#define NoDepostTask 30
#define NoWithdrawTask 10

void depositTask(BankAccount& bnkacc, int amount){
    for (int i = 0; i < NoDepostTask; i++) {
        bnkacc.deposit(amount);
        //cout << "Deposit thread" << endl;
    }
}

void withdrawTask(BankAccount& bnkacc, int amount) {
    for (int i = 0; i < NoWithdrawTask; i++) {
        bnkacc.withdraw(amount);
        //cout << "Withdraw thread" << endl;
    }
}

int main()
{
    BankAccount account(1000);

    std::thread t1(depositTask, std::ref(account), 10);
    std::thread t2(withdrawTask, std::ref(account), 10);

    t1.join();
    t2.join();

    std::cout << "Final balance is: " << account.getBalance() << std::endl;
    
    return 0;
}

