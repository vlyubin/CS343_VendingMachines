#include "printer.h"

_Task VendingMachine;

#ifndef NAME_SERVER_H_
#define NAME_SERVER_H_

_Task NameServer {
    Printer &printer;
    unsigned int numVendingMachines, numStudents;

    void main();
  public:
    NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents);
    void VMregister(VendingMachine *vendingmachine);
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif // NAME_SERVER_H_
