#ifndef WATCARD_OFFICE_H_
#define WATCARD_OFFICE_H_

#include "watcard.h"
#include <queue>
#include <vector>

_Monitor Bank;
_Monitor Printer;

_Task WATCardOffice {
		/* Copying the WATCardOffice is not allowed. */
		WATCardOffice(const WATCardOffice&);
		WATCardOffice& operator=(const WATCardOffice&);

		/* A job contains all the information necessary for a courier to transfer
		 * funds to a student's watcard. Public method calls to the WATCardOffice
		 * may cause jobs to be created, which are assigned to available couriers.
		 */
    struct Job {                 // marshalled arguments and return future
				struct Args {
					Bank& bank;            // Bank to transfer from
					unsigned int sid;      // Student id. Transfer from the bank account of this student.
					unsigned int amount;   // How much to trasfer in dollars
					WATCard* card;         // If not null, transfer onto this card, 
					                       //   otherwise create a new card and trasfer to it.
					Args(Bank& bank, unsigned int sid, unsigned int amount, WATCard* card = NULL)
						: bank(bank), sid(sid), amount(amount), card(card) {}
				};
        Args args;                 // call arguments
        WATCard::FWATCard result;  // return future
        Job(Args args) : args(args) {}
    }; // Job

		/* These are helper tasks that execute jobs on behalf of the WATCardOffice.
		 * A courier gets a job from the WATCardOffice, then withdraws the specified
		 * funds from a student's bank account and adds it to a watcard. Once funds
		 * have been added to the watcard, the future Job::result is updated with
		 * the watcard and the job is deleted. */
    _Task Courier {
			WATCardOffice& office; // Watcard office to get jobs from
			Printer& printer;      // Print using this printer.
			const unsigned int id; // Unique id
			void main();
			enum state { Start = 'S', StartTransfer = 't', CompleteTransfer = 'T',
				Finish = 'F'};       // States for printing
		 public:
			Courier(WATCardOffice& office, Printer& printer, unsigned int id);
		}; // Courier            Communicates with bank

    void main();

		Courier** couriers; // Array of courier pointers. Initialized in constructor
		Printer& printer;
		Bank& bank;
		const unsigned int numCouriers;
		std::queue<Job*> jobQueue; // Queue of pending jobs that have not yet been assigned to a courier.
		uCondition availableJobs;  // This condition variable is signalled whenever there is an available job.
		Job* newJob;               // Set when a public method creates a new job

		/* inDestructor and KILL_YOURSELF are used to clean up the couriers when the
		 * WATCardOffice is deleted. In the destructor, any waiting couriers are
		 * woken up and given the job pointer KILL_YOURSELF. inDestructor is an
		 * internal flag used to indicate to the requestWork() public method that
		 * KILL_YOURSELF should be returned.
		 * Any couriers receiving the KILL_YOURSELF job should immediately terminate
		 * their main loop so that they may be destroyed */
		bool inDestructor; 
		static Job* const KILL_YOURSELF;

		enum states { Start = 'S', Create = 'C', Transfer = 'T', Work = 'W',
			Finish = 'F' }; // States for printing

  public:
		/* This exception can be thrown by a FWATCard future.
		 * It means the WATCard has been lost and must be-recreated.
		 * Any money on the WATCard is lost forever. */
    _Event Lost {};

		/* Create a watcard office with numCouriers courier threads. */
    WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers);
		~WATCardOffice(); // Delete the watcard office and all associated courier threads.

		/* Create a new WATCard with balance $amount taken from the bank account of
		 * student with id 'sid' */
    WATCard::FWATCard create(unsigned int sid, unsigned int amount);
		/* Transfer $amount onto the watcard 'card' from the bank account of the
		 * student with id 'sid' */
    WATCard::FWATCard transfer(unsigned int sid, unsigned int amount, 
            WATCard *card);

		/* Called by the couriers to get a new job to process.
		 * Either returns a job pointer or the value WATCardOffice::KILL_YOURSELF
		 * KILL_YOURSELF is returned when the destructor of WATCardOffice has been
		 * called and the couriers need to terminate. */
    Job *requestWork();

}; // WATCardOffice

#endif // WATCARD_OFFICE_H_
