#include "bottlingPlant.h"

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
  printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
  maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
  timeBetweenShipments(timeBetweenShipments) {
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
  return false; // TODO
}

void BottlingPlant::main() {
  // TODO
}
