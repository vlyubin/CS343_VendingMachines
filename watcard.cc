#include "watcard.h"
#include <cassert>

WATCard::WATCard(): balance(0) {}

void WATCard::deposit(unsigned int amount) {
	balance += amount;
} // WATCard::deposit

void WATCard::withdraw(unsigned int amount) {
	assert(balance >= amount);
	balance -= amount;
} // WATCard::withdraw

unsigned int WATCard::getBalance() {
	return balance;
} // WATCard::getBalance
