#include "nameServer.h"
#include "vendingMachine.h"
#include "printer.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents), nextId(0) {
  machines = new VendingMachine*[numVendingMachines];
  studentPosition = new unsigned int[numStudents];
} // NameServer::NameServer

NameServer::~NameServer() {
  delete [] machines;
  delete [] studentPosition;
} // NameServer::~NameServer

void NameServer::VMregister(VendingMachine *vendingmachine) {
  printer.print(Printer::NameServer, RegisterVM, (int)vendingmachine->getId());
  machines[nextId] = vendingmachine;
  nextId++;
} // NameServer::VMregister

VendingMachine* NameServer::getMachine(unsigned int id) {
  assert(studentPosition[id] >= 0 && studentPosition[id] < numVendingMachines &&
      "Invalid machine for student in nameServer data");
  unsigned int postion = studentPosition[id];
  studentPosition[id] = (studentPosition[id] + 1) % numVendingMachines;

  printer.print(Printer::NameServer, NewVM, (int)id, (int)machines[postion]->getId());

  return machines[postion];
} // NameServer::getMachine

VendingMachine** NameServer::getMachineList() {
  return machines;
} // NameServer::getMachineList

void NameServer::main() {
  printer.print(Printer::NameServer, Starting);

  // Wait until all vending machines register
  for (size_t i = 0; i < numVendingMachines; i++) {
    _Accept(VMregister);
  } // for

  // Split students into initial buckets
  for (size_t i = 0; i < numStudents; i++) {
    studentPosition[i] = i % numVendingMachines;
  } // for

  while (true) {
    _Accept(getMachine) {
    } or _Accept(getMachineList) {
    } or _Accept(~NameServer) { // Used to indicate termination
      break;
    } // _Accept
  } // while

  printer.print(Printer::NameServer, Finished);
} // NameServer::main
