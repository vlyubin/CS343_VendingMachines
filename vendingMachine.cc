#include "vendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
    unsigned int maxStockPerFlavour) : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost),
  maxStockPerFlavour(maxStockPerFlavour) {
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
  return VendingMachine::BUY; //TODO
}

unsigned int* VendingMachine::inventory() {
  return NULL;
}

void VendingMachine::restocked() {
}

_Nomutex unsigned int VendingMachine::cost() {
  return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
  return id;
}

void VendingMachine::main() {
}
