#include "watcardOffice.h"
#include "printer.h"
#include <cassert>

WATCardOffice::Job* const WATCardOffice::KILL_YOURSELF = NULL;

WATCardOffice::WATCardOffice(Printer& prt, Bank& bank, 
		unsigned int numCouriers)
		: printer(prt), bank(bank), numCouriers(numCouriers),
			inDestructor(false) {
	
	couriers = new Courier*[numCouriers];
	for (unsigned int i = 0; i < numCouriers; ++i) {
		couriers[i] = new Courier(*this, printer);
	}
}
	
WATCardOffice::~WATCardOffice() {
	inDestructor = true;
	assert(jobQueue.empty());
	while (!availableJobs.empty()) {
		availableJobs.signalBlock();
	}

	for (unsigned int i = 0; i < numCouriers; ++i) {
		delete couriers[i];
	}
	delete[] couriers;
}

void WATCardOffice::main() {
	printer.print(Printer::WATCardOffice, Start);
	while (true) {
		_Accept(create) {
			jobQueue.push(newJob);
			availableJobs.signalBlock();
			printer.print(Printer::WATCardOffice, (char)Create, newJob->args.sid,
				newJob->args.amount);

		} or _Accept(transfer) {
			jobQueue.push(newJob);
			availableJobs.signalBlock();
			printer.print(Printer::WATCardOffice, (char)Transfer, newJob->args.sid,
				newJob->args.amount);

		} or _Accept(requestWork) {
			printer.print(Printer::WATCardOffice, (char)Work);

		} or _Accept(~WATCardOffice) {
			break;
		}
	}
	printer.print(Printer::WATCardOffice, Finish);
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount){
	newJob = new Job(Job::Args(bank, sid, amount));
	return newJob->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount,
		WATCard* card) {
	newJob = new Job(Job::Args(bank, sid, amount, card));
	return newJob->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	if (jobQueue.empty()) {
		availableJobs.wait();
		if (inDestructor) {
			return KILL_YOURSELF;
		}

		assert(!jobQueue.empty());
	}
	Job* job = jobQueue.front();
	jobQueue.pop();
	return job;
}
