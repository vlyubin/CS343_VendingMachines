#ifndef WATCARD_OFFICE_H_
#define WATCARD_OFFICE_H_

#include "watcard.h"
#include <queue>
#include <vector>

_Monitor Bank;
_Monitor Printer;

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
				struct Args {
					Bank& bank;            // Bank to transfer from
					unsigned int sid;      // Student id
					unsigned int amount;   // How much to trasfer
					WATCard* card;         // If set, transfer onto this card, 
					                       //   otherwise create a new card
					Args( Bank& bank, unsigned int sid, unsigned int amount, WATCard* card = NULL )
						: bank( bank ), sid( sid ), amount( amount ), card( card ) {}
				};
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };

    _Task Courier {
			WATCardOffice& office;
			Printer& printer;
			void main();
			enum state { Start = 'S', StartTransfer = 't', CompleteTransfer = 'T',
				Finish = 'F'};
		 public:
			Courier( WATCardOffice& office, Printer& printer );
		};                 // communicates with bank

    void main();

		Courier** couriers;
		Printer& printer;
		Bank& bank;
		const unsigned int numCouriers;
		std::queue<Job*> jobQueue;
		uCondition availableJobs;
		Job* newJob; // Set when a public member creates a new job
		bool inDestructor;

		// This can be returned from requestWork to indicate to a courier that it
		// should terminate.
		static Job* const KILL_YOURSELF;

		enum states { Start = 'S', Create = 'C', Transfer = 'T', Work = 'W',
			Finish = 'F' };

  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
		~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, 
            WATCard *card );
		/* Either returns a job pointer or value WATCardOffice::KILL_YOURSELF
		 * KILL_YOURSELF is returned when the destructor of WATCardOffice has been
		 * called and the couriers need to terminate. */
    Job *requestWork();
};

#endif // WATCARD_OFFICE_H_
