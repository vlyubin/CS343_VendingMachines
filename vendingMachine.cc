#include "vendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
    unsigned int maxStockPerFlavour) : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost),
    maxStockPerFlavour(maxStockPerFlavour), soda(new unsigned int[NUM_FLAVOURS]) {
  // Initially VM is empty
  for (size_t i = 0; i < NUM_FLAVOURS; i++) {
    soda[i] = 0;
  }
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
  if (soda[flavour] == 0) {
    return STOCK; // No more soda of this flavour left
  } else if (card.getBalance() < sodaCost) {
    return FUNDS; // Not enough funds to purchase a bottle
  }

  // Otherwise we have enough funds and can complete the purchase
  card.withdraw(sodaCost); // Pay for soda
  soda[flavour]--; // Update soda count

  printer.print(Printer::Vending, id, Bought, (int)flavour, (int)soda[flavour]);

  return VendingMachine::BUY; // Success
}

unsigned int* VendingMachine::inventory() {
  printer.print(Printer::Vending, id, (char)StartReloading);
  return soda;
}

void VendingMachine::restocked() {
  printer.print(Printer::Vending, id, (char)CompleteReloading);
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
  printer.print(Printer::Vending, id, (char)Starting, (int)sodaCost);
  nameServer.VMregister(this);

  while (true) {
    _Accept(buy) {
    } or _Accept(inventory) {

      // Don't accept buy while restocking; wait for the restocked() call
      _Accept(restocked) {}

    } or _Accept(~VendingMachine) {
      break;
    }
  }

  printer.print(Printer::Vending, id, (char)Finished);
}
