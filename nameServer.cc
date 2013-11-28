#include "nameServer.h"
#include "vendingMachine.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents), nextId(0) {
  machines = new VendingMachine*[numVendingMachines];
  studentPosition = new unsigned int[numStudents];
}

NameServer::~NameServer() {
  delete [] machines;
  delete [] studentPosition;
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
  printer.print(Printer::NameServer, RegisterVM, (int)vendingmachine->getId());
  machines[nextId] = vendingmachine;
  nextId++;
}

VendingMachine* NameServer::getMachine(unsigned int id) {
  unsigned int postion = studentPosition[id];
  studentPosition[id] = (studentPosition[id] + 1) % numVendingMachines;

  printer.print(Printer::NameServer, NewVM, (int)id, (int)machines[postion]->getId());

  return machines[postion];
}

VendingMachine** NameServer::getMachineList() {
  return machines;
}

void NameServer::main() {
  printer.print(Printer::NameServer, Starting);

  // Wait until all vending machines register
  for (size_t i = 0; i < numVendingMachines; i++) {
    _Accept(VMregister);
  }

  for (size_t i = 0; i < numStudents; i++) {
    studentPosition[i] = i % numVendingMachines;
  }

  while (true) {
    _Accept(getMachine) {
    } or _Accept(getMachineList) {
    } or _Accept(~NameServer) {
      break;
    }
  }

  printer.print(Printer::NameServer, Finished);
}
