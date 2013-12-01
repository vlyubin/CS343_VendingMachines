#include "bank.h"
#include <cassert>

Bank::Bank(unsigned int numStudents)
#ifndef NDEBUG
		: numStudents(numStudents)
#endif
		{

	balance = new unsigned int[numStudents];
	for (unsigned int i = 0; i < numStudents; ++i) {
		balance[i] = 0;
	}
	deposited = new uCondition[numStudents];
} // Bank::Bank

Bank::~Bank() {
	delete[] balance;
	delete[] deposited;
} // Bank::~Bank

void Bank::deposit(unsigned int id, unsigned int amount) {
	assert(id < numStudents);
	balance[id] += amount;
	deposited[id].signal();
} // Bank::deposit

void Bank::withdraw(unsigned int id, unsigned int amount) {
	assert(id < numStudents);
	while (balance[id] < amount) {
		deposited[id].wait();
	}
	balance[id] -= amount;
} // Bank::withdraw
