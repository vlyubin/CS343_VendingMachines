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
		_Accept( create ) {
			jobQueue.push( newJob );
			availableJobs.signal();

		} or _Accept( transfer ) {
			jobQueue.push( newJob );
			availableJobs.signal();

		} or _Accept( requestWork ) {
		} or _Accept( ~WATCardOffice ) {
			break;
		}
	}
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){
	newJob = new Job( Job::Args( bank, sid, amount ) );
	return newJob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount,
		WATCard* card ) {
	newJob = new Job( Job::Args( bank, sid, amount, card ) );
	return newJob->result;
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
