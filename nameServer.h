#ifndef NAME_SERVER_H_
#define NAME_SERVER_H_

_Task VendingMachine;
_Monitor Printer;

_Task NameServer {
    Printer &printer;
    const unsigned int numVendingMachines;
    const unsigned int numStudents;
    VendingMachine** machines;
    unsigned int nextId; // Used to indicate the position in the list where the next machine will go
    unsigned int* studentPosition; // Used to indicate the position of the machine that each student
    // has to try next. studentPosition[id] is the index in machines array that student with id id
    // should use next

    // States we can print for NameServer
    enum States {Starting = 'S', RegisterVM = 'R', NewVM = 'N', Finished = 'F'};
    void main();
  public:
    NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents);
    ~NameServer();
    void VMregister(VendingMachine *vendingmachine); // Add the specified VM to list of machines
    VendingMachine *getMachine(unsigned int id); // Returns a pointer to machine that student with id id
    // should use next
    VendingMachine **getMachineList(); // Return the list of registered machines
}; // NameServer

#endif // NAME_SERVER_H_
