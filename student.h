#ifndef STUDENT_H_
#define STUDENT_H_

_Monitor Printer;
_Task NameServer;
_Task WATCardOffice;

_Task Student {
	Printer& printer;
	NameServer& nameServer;
	WATCardOffice& cardOffice;
	const unsigned int id;
	const unsigned int maxPurchases;

  enum States {Starting = 'S', SelectingVM = 'V', Bought = 'B', LostCard = 'L',
      Finished = 'F'};	// States for printing
	void main();
 public:
	Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
		unsigned int maxPurchases);
}; // Student

#endif // STUDENT_H_
