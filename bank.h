#ifndef BANK_H_
#define BANK_H_

_Monitor Bank {
#ifndef NDEBUG
	// Only needed for bounds checking when debugging
	unsigned int numStudents;
#endif
	unsigned int *balance;
	uCondition *deposited;

  public:
    Bank(unsigned int numStudents);
		~Bank();
    void deposit(unsigned int id, unsigned int amount);
    void withdraw(unsigned int id, unsigned int amount);
};

#endif // BANK_H_
