#ifndef WATCARD_OFFICE_H_
#define WATCARD_OFFICE_H_

#include "watcard.h"

_Monitor Bank;

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
				struct Args { // TODO
				};
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };
    //TODO: _Task Courier { ... };                 // communicates with bank

    void main();
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, 
			WATCard *card );
    Job *requestWork();
};

#endif // WATCARD_OFFICE_H_
