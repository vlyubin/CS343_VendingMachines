#include "parent.h"
#include "bank.h"
#include "MPRNG.h"
#include "printer.h"

void Parent::main() {
	printer.print(Printer::Parent, Start);
	while (true) {
		_Accept(~Parent) { // Quit when destructor is called
			break;
		} _Else {
			yield(parentalDelay);
			unsigned int studentID = randGen(numStudents - 1); // Pick a random student
			unsigned int amount = randGen(minAmountToDeposit, maxAmountToDeposit); // Random amount of money to deposit
			bank.deposit(studentID, amount);
			printer.print(Printer::Parent, (char)Deposit, studentID, amount);
		} // _Accept
	} // while
	printer.print(Printer::Parent, Finish);
} // Parent::main

Parent::Parent(Printer& prt, Bank& bank, unsigned int numStudents,
		unsigned int parentalDelay)
		: printer(prt), bank(bank), numStudents(numStudents),
		  parentalDelay(parentalDelay) {
} // Parent::Parent
