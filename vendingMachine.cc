#include "vendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
    unsigned int maxStockPerFlavour) : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost),
  maxStockPerFlavour(maxStockPerFlavour), soda(new unsigned int[NUM_FLAVOURS]) {
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
  return VendingMachine::BUY; //TODO
}

unsigned int* VendingMachine::inventory() {
  return soda;
}

void VendingMachine::restocked() {
  // TODO
}

_Nomutex unsigned int VendingMachine::cost() {
  return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
  return id;
}

VendingMachine::~VendingMachine() {
  delete [] soda;
}

void VendingMachine::main() {
  nameServer.VMregister(this);

  while (true) {
    _Accept(buy) {

    } or _Accept(inventory) {

    } or _Accept(restocked) {

    } or _Accept(~VendingMachine) {
      break;
    }
  }
}
