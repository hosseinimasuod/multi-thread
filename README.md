# Bank Account Simulation with Multi-Threading

This project simulates a bank account system with support for multi-threaded deposits, withdrawals, and transfers. It uses mutexes to ensure thread safety and includes a logging mechanism to track transactions.

## Features
- **Deposit**: Add money to an account.
- **Withdraw**: Remove money from an account (if sufficient balance is available).
- **Transfer**: Transfer money between two accounts.
- **Logging**: All transactions are logged to a file (`transactions.log`) with timestamps.
