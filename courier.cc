#include "bank.h"
#include "MPRNG.h"
#include "printer.h"
#include "watcard.h"
#include "watcardOffice.h"

void WATCardOffice::Courier::main() {
	printer.print(Printer::Courier, Start);
	while (true) {
		Job* job = office.requestWork();
		if (job == KILL_YOURSELF) {
			break;
		}

		if (job->args.card == NULL) {
			job->args.card = new WATCard();
		}
		printer.print(Printer::Courier, (char)StartTransfer, job->args.sid,
			job->args.amount);

		job->args.bank.withdraw(job->args.sid, job->args.amount);
		try {
			job->args.card->deposit(job->args.amount);
		} catch (uCondition::WaitingFailure) {
			break;
		}
		
		printer.print(Printer::Courier, (char)CompleteTransfer,
			job->args.sid, job->args.amount);

		if (randGen(1, 6) == 1) {
			// Lost the card
			delete job->args.card;
			job->result.exception(new Lost());
		} else {
			job->result.delivery(job->args.card);
		}

		delete job;
	}
}

WATCardOffice::Courier::Courier(WATCardOffice& office, Printer& printer)
	: office(office), printer(printer) {
}
