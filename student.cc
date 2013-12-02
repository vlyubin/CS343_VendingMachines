#include "student.h"
#include "constants.h"
#include "MPRNG.h"
#include "nameServer.h"
#include "printer.h"
#include "vendingMachine.h"
#include "watcard.h"
#include "watcardOffice.h"

#define WATCARD_BASE_BALANCE 5

void Student::main() {
	unsigned int bottlesToPurchase = randGen(1, maxPurchases); // random number of bottles to purchase
	VendingMachine::Flavours favouriteFlavour =
		static_cast<VendingMachine::Flavours>(randGen(NUM_FLAVOURS)); // random favourite flavour
	
	printer.print(Printer::Student, id, Starting, (int)favouriteFlavour, (int)bottlesToPurchase);

	WATCard::FWATCard watcard = cardOffice.create(id, WATCARD_BASE_BALANCE); // create WATCard future with $5
	VendingMachine* machine = nameServer.getMachine(id); // get a vending machine from the name server
	printer.print(Printer::Student, id, (char)SelectingVM, (int)machine->getId());

	while (bottlesToPurchase > 0) { // buys one bottle on each loop iteration
		yield(randGen(1, 10));

		RetryBuy: while (true) { // loop until student manages to buy a bottle
			try {
				VendingMachine::Status status =
					machine->buy(favouriteFlavour, *(watcard())); // attempt to buy a soda bottle

				switch(status) {
				 case VendingMachine::BUY:
				 	// Successfully bought a bottle. Stop retrying.
				 	break RetryBuy;

				 case VendingMachine::STOCK:
				 	// Vending machine is out of stock. Try another.
					nameServer.getMachine(id);
					printer.print(Printer::Student, id, (char)SelectingVM, (int)machine->getId());
					break;
				 
				 case VendingMachine::FUNDS:
				 	// Insufficient funds; transfer more money.
				 	watcard = cardOffice.transfer(id, WATCARD_BASE_BALANCE + machine->cost(), watcard);
					break;

				 default:
				 	assert(false && "Invalid vending machine status!");
				} // switch

			} catch (const WATCardOffice::Lost& e) { // Watcard was lost
				printer.print(Printer::Student, id, (char)LostCard);
				watcard = cardOffice.create(id, WATCARD_BASE_BALANCE); // Create a new new watcard with $5
			} // try
		} // while

		bottlesToPurchase -= 1;
		printer.print(Printer::Student, id, (char)Bought, (int)watcard()->getBalance());
	} // while

	// The student is responsible for deleting their watcard when the are done
	// with it.
	delete watcard();

	printer.print(Printer::Student, id, (char)Finished);
} // Student::main

Student::Student(Printer &prt, NameServer &nameServer,
		WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases)
		: printer(prt), nameServer(nameServer), cardOffice(cardOffice), 
		  id(id), maxPurchases(maxPurchases) {
} // Student::Student
