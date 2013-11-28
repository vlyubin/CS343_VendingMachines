#ifndef PARENT_H_
#define PARENT_H_

_Monitor Printer;
_Monitor Bank;

_Task Parent {
    void main();
		Printer& printer;
		Bank& bank;
		const unsigned int numStudents;
		const unsigned int parentalDelay;

		enum states { Start = 'S', Deposit = 'D', Finish = 'F' };
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif // PARENT_H_
