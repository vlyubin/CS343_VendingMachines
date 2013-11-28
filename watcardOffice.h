#ifndef WATCARD_OFFICE_H_
#define WATCARD_OFFICE_H_

#include "watcard.h"
#include <queue>

_Monitor Bank;
_Monitor Printer;

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
				struct Args {
					Bank& bank;
					unsigned int sid;
					unsigned int amount;
					Args( Bank& bank, unsigned int sid, unsigned int amount )
						: bank( bank ), sid( sid ), amount( amount ) {}
				};
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };

    _Task Courier {
			void main();
		};                 // communicates with bank

    void main(); // TODO: Does anything need to go in here?

		Courier* couriers;
		Printer& printer;
		Bank& bank;
		const unsigned int numCouriers;
		std::queue<Job*> jobQueue;
		uCondition availableJobs;

  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
		~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, 
			WATCard *card );
    Job *requestWork();
};

#endif // WATCARD_OFFICE_H_
