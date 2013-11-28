#include "watcardOffice.h"
#include "printer.h"
#include <cassert>

WATCardOffice::WATCardOffice( Printer& prt, Bank& bank, 
		unsigned int numCouriers )
		: printer( prt ), bank( bank ), numCouriers( numCouriers ) {
	couriers = new Courier[ numCouriers ];
}
	
WATCardOffice::~WATCardOffice() {
	assert( jobQueue.empty() );
	delete[] couriers;
}

void WATCardOffice::main() {
	while (true) {
		_Accept(create, transfer, requestWork, ~WATCardOffice);
	}
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){
	Job::Args args( bank, sid, amount );
	Job *job = new Job( args );
	jobQueue.push( job );
	availableJobs.signal();
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount,
		WATCard* card ) {
	Job::Args args( bank, sid, amount + card->getBalance() );
	delete card;

	Job *job = new Job( args );
	jobQueue.push( job );
	availableJobs.signal();
	return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	if ( jobQueue.empty() ) {
		availableJobs.wait();
		assert( !jobQueue.empty() );
	}
	Job* job = jobQueue.front();
	jobQueue.pop();
	return job;
}
