#include "nameServer.h"
#include "vendingMachine.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
}

VendingMachine* NameServer::getMachine(unsigned int id) {
  return NULL;
}

VendingMachine** NameServer::getMachineList() {
  return NULL;
}

void NameServer::main() {
}