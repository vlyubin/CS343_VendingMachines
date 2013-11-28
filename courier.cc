#include "bank.h"
#include "watcard.h"
#include "watcardOffice.h"
#include "MPRNG.h"

void WATCardOffice::Courier::main() {
	while (true) {
		Job* job = office.requestWork();
		if ( job == KILL_YOURSELF ) {
			break;
		}

		if ( job->args.card == NULL ) {
			job->args.card = new WATCard();
		}

		job->args.bank.withdraw( job->args.sid, job->args.amount );
		job->args.card->deposit( job->args.amount );
		// TODO: Check if we need to die

		if ( randGen( 1, 6 ) == 1 ) {
			// Lost the card
			delete job->args.card;
			job->result.exception( new Lost() );
		} else {
			job->result.delivery( job->args.card );
		}
	}
}

WATCardOffice::Courier::Courier( WATCardOffice& office )
	: office( office ) {
}
