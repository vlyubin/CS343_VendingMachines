#include "student.h"
#include "MPRNG.h"
#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "watcard.h"
#include "vendingMachine.h"

void Student::main() {
	unsigned int bottlesToPurchase = randGen(1, maxPurchases);
	VendingMachine::Flavours favouriteFlavour =
		static_cast<VendingMachine::Flavours>(randGen(0, 3));
	
	printer.print(Printer::Student, id, Starting, (int)favouriteFlavour, (int)bottlesToPurchase);

	WATCard::FWATCard watcard = cardOffice.create(id, 5);
	VendingMachine* machine = nameServer.getMachine(id);
	printer.print(Printer::Student, id, (char)SelectingVM, (int)machine->getId());

	while (bottlesToPurchase > 0) {
		yield(randGen(1, 10));

		bool boughtSoda = false;
		while (!boughtSoda) {
			try {
				VendingMachine::Status status =
					machine->buy( favouriteFlavour, *(watcard()) );

				switch(status) {
				 case VendingMachine::BUY:
				 	bottlesToPurchase -= 1;
					boughtSoda = true;
					printer.print(Printer::Student, id, (char)Bought, (int)watcard()->getBalance());
					break;

				 case VendingMachine::STOCK:
				 	// Try another machine
					nameServer.getMachine(id);
					break;
				 
				 case VendingMachine::FUNDS:
				 	// Insufficient funds; transfer more money.
				 	watcard = cardOffice.transfer( id, 5 + machine->cost(), watcard );
					break;

				 default:
				 	assert(false && "Invalid vending machine status!");
				}
				 	
			} catch (const WATCardOffice::Lost& e) {
				printer.print(Printer::Student, id, (char)LostCard);
				watcard = cardOffice.create(id, 5);
			}
		}
	}

	// The student is responsible for deleting their watcard when the are done
	// with it.
	delete watcard();

	printer.print(Printer::Student, id, (char)Finished);
}

Student::Student(Printer &prt, NameServer &nameServer,
		WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases)
		: printer(prt), nameServer(nameServer), cardOffice(cardOffice), 
		  id(id), maxPurchases(maxPurchases) {
}
