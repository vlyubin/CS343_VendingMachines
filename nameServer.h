#include "printer.h"

_Task VendingMachine;

#ifndef NAME_SERVER_H_
#define NAME_SERVER_H_

_Task VendingMachine;

_Task NameServer {
    Printer &printer;
    unsigned int numVendingMachines, numStudents;
    VendingMachine** machines;
    enum States {Starting = 'S', RegisterVM = 'R', NewVM = 'N', Finished = 'F'};
    unsigned int nextId;
    unsigned int* studentPosition;

    void main();
  public:
    NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents);
    ~NameServer();
    void VMregister(VendingMachine *vendingmachine);
    VendingMachine *getMachine(unsigned int id);
    VendingMachine **getMachineList();
};

#endif // NAME_SERVER_H_
