#include "watcardOffice.h"
#include "printer.h"
#include <cassert>

WATCardOffice::Job* const WATCardOffice::KILL_YOURSELF = NULL;

WATCardOffice::WATCardOffice(Printer& prt, Bank& bank, 
		unsigned int numCouriers)
		: printer(prt), bank(bank), numCouriers(numCouriers),
			inDestructor(false) {
	
	// Create numCouriers courier threads
	couriers = new Courier*[numCouriers];
	for (unsigned int i = 0; i < numCouriers; ++i) {
		couriers[i] = new Courier(*this, printer);
	} // for
} // WATCardOffice::WATCardOffice
	
WATCardOffice::~WATCardOffice() {
	inDestructor = true;
	assert(jobQueue.empty());

	// Wake up all the couriers so they can terminate.
	while (!availableJobs.empty()) {
		availableJobs.signalBlock();
	} // while

	// Delete the couriers and the array holding them.
	for (unsigned int i = 0; i < numCouriers; ++i) {
		delete couriers[i];
	} // for
	delete[] couriers;
} // WATCardOffice::~WATCardOffice

void WATCardOffice::main() {
	printer.print(Printer::WATCardOffice, Start);
	while (true) { // Main server loop; accept a method call on each iteration.
		_Accept(create) {           // Create a new watcard. Server tracks the job.
			jobQueue.push(newJob);    // newJob was created by caller in public method
			availableJobs.signalBlock();
			printer.print(Printer::WATCardOffice, (char)Create, newJob->args.sid,
				newJob->args.amount);

		} or _Accept(transfer) {    // Transfer money onto a watcard. Server tracks the job.
			jobQueue.push(newJob);
			availableJobs.signalBlock();
			printer.print(Printer::WATCardOffice, (char)Transfer, newJob->args.sid,
				newJob->args.amount);

		} or _Accept(requestWork) { // Gives a job to a courier. Nothing for the server to do.
			printer.print(Printer::WATCardOffice, (char)Work);

		} or _Accept(~WATCardOffice) { // Accept destructor to break out of main loop.
			break;
		} // _Accept
	} // while
	printer.print(Printer::WATCardOffice, Finish);
} // WATCardOffice::main

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount){
	newJob = new Job(Job::Args(bank, sid, amount)); // Create a new job. The server will manage it.
	return newJob->result; // Return the future in the job.
} // WATCardOffice::create

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount,
		WATCard* card) {
	newJob = new Job(Job::Args(bank, sid, amount, card));
	return newJob->result;
} // WATCardOffice::transfer

WATCardOffice::Job* WATCardOffice::requestWork() {
	if (inDestructor) {
		return KILL_YOURSELF;
	} // if

	if (jobQueue.empty()) {
		availableJobs.wait();
		if (inDestructor) {
			// If inDestructor is true then the condition variable was signalled
			// because WATCardOffice is being destroyed, not because a job is
			// available.
			return KILL_YOURSELF;
		} // if

		assert(!jobQueue.empty());
	} // if
	// Get a new job from the front of the queue and return it.
	Job* job = jobQueue.front();
	jobQueue.pop();
	return job;
} // WATCardOffice::requestWork()
