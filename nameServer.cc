#include "nameServer.h"
#include "vendingMachine.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
  machines = new VendingMachine*[numVendingMachines];
}

NameServer::~NameServer() {
  delete [] machines;
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
  machines[vendingmachine->getId()] = vendingmachine;
}

VendingMachine* NameServer::getMachine(unsigned int id) {
  return machines[id % numVendingMachines]; // TODO
}

VendingMachine** NameServer::getMachineList() {
  return machines;
}

void NameServer::main() {
  // Wait until all vending machines register
  for (size_t i = 0; i < numVendingMachines; i++) {
    _Accept(VMregister);
  }

  while (true) {
    _Accept(getMachine) {
    } or _Accept(getMachineList) {
    } or _Accept(~NameServer) {
      break;
    }
  }
}