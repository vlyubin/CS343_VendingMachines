#include "bank.h"
#include "MPRNG.h"
#include "printer.h"
#include "watcard.h"
#include "watcardOffice.h"

void WATCardOffice::Courier::main() {
	printer.print(Printer::Courier, id, (char)Start);
	while (true) {
		Job* job = office.requestWork();
		if (job == KILL_YOURSELF) { // termination condition
			break;
		} // if

		if (job->args.card == NULL) {
			// job requires the creation of a new watcard.
			job->args.card = new WATCard();
		} // if
		printer.print(Printer::Courier, id, (char)StartTransfer, job->args.sid,
			job->args.amount);

		// Get money from the bank and deposit it in the watcard.
		// Note: withdraw can block on a condition variable in bank so the couriers
		// (and hence WATCardOffice) must be deleted before Bank.
		job->args.bank.withdraw(job->args.sid, job->args.amount);
		job->args.card->deposit(job->args.amount);
		
		printer.print(Printer::Courier, id, (char)CompleteTransfer,
			job->args.sid, job->args.amount);

		if (randGen(1, 6) == 1) {
			// Lost the card
			delete job->args.card;                // Delete the lost card
			job->result.exception(new Lost());    // Pass the Lost exception to the WATCard future
		} else {
			job->result.delivery(job->args.card); // Pass the watcard to the future.
		} // if

		delete job; // Courier is responsible for deleting the job
	} // while

	printer.print(Printer::Courier, id, (char)Finish);
} // WATCardOffice::Courier::main

WATCardOffice::Courier::Courier(WATCardOffice& office, Printer& printer,
	unsigned int id): office(office), printer(printer), id(id) {
} // WATCardOffice::Courier::Courier
