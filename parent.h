#ifndef PARENT_H_
#define PARENT_H_

_Monitor Printer;
_Monitor Bank;

/* Parent is a task that repeatedly deposits money into the bank account of a
 * random student. Parent continues until it is deleted. */
_Task Parent {
    void main();
		Printer& printer;
		Bank& bank;
		const unsigned int numStudents;
		const unsigned int parentalDelay; // How many times to yield before depositing money

		/* Range of how much money to deposit in accounts. */
		enum { minAmountToDeposit = 1, maxAmountToDeposit = 3 }; 
		enum states { Start = 'S', Deposit = 'D', Finish = 'F' }; // States for printing
  public:
    Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay);
};

#endif // PARENT_H_
