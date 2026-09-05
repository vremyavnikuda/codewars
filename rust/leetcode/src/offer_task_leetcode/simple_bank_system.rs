#!/usr/bin/env rust-script

pub struct Bank {
    balances: Vec<i64>,
    total_accounts: usize,
}

impl Bank {
    fn new(balance: Vec<i64>) -> Self {
        let total_accounts = balance.len();
        Bank {
            balances: balance,
            total_accounts,
        }
    }

    fn transfer(&mut self, account1: i32, account2: i32, money: i64) -> bool {
        let from = match self.account_index(account1) {
            Some(index) => index,
            None => return false,
        };

        let to = match self.account_index(account2) {
            Some(index) => index,
            None => return false,
        };

        if self.balances[from] < money {
            return false;
        }

        self.balances[from] -= money;
        self.balances[to] += money;
        true
    }

    fn deposit(&mut self, account: i32, money: i64) -> bool {
        match self.account_index(account) {
            Some(index) => {
                self.balances[index] += money;
                true
            }
            None => false,
        }
    }

    fn withdraw(&mut self, account: i32, money: i64) -> bool {
        let index = match self.account_index(account) {
            Some(index) => index,
            None => return false,
        };

        if self.balances[index] < money {
            return false;
        }

        self.balances[index] -= money;
        true
    }

    fn account_index(&self, account: i32) -> Option<usize> {
        if account >= 1 && (account as usize) <= self.total_accounts {
            Some((account - 1) as usize)
        } else {
            None
        }
    }
}

fn main() {
    let balance = vec![10, 100, 20, 50, 30];
    let mut bank = Bank::new(balance);

    println!("Bank initialized with balance: [10, 100, 20, 50, 30]");
    println!("Withdraw 10 from account 3: {}", bank.withdraw(3, 10));
    println!(
        "Transfer 5 from account 1 to account 2: {}",
        bank.transfer(1, 2, 5)
    );
    println!("Deposit 20 to account 5: {}", bank.deposit(5, 20));
}
