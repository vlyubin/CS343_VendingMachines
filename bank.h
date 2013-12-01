#ifndef BANK_H_
#define BANK_H_

_Monitor Bank {
#ifndef NDEBUG
	// Only needed for bounds checking when debugging
	unsigned int numStudents;
#endif
	/* Array of student balances (bank accounts) indexed by student IDs. */
	unsigned int *balance;
	/* Array of condition variables indexed by student IDs.
	 * A condition variable is signalled when money is deposited into the
	 * associated account. */
	uCondition *deposited;

  public:
		/* Initialize a bank with accounts for numStudents, each having a balance of
		 * $0 */
    Bank(unsigned int numStudents);
		~Bank();
		/* Deposit $amount into the account of student with given id. */
    void deposit(unsigned int id, unsigned int amount);
		/* Withdraw $amount from the account of student with given id. */
    void withdraw(unsigned int id, unsigned int amount);
}; // Bank

#endif // BANK_H_
