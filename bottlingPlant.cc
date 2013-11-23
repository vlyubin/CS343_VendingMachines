#include "bottlingPlant.h"
#include "truck.h"

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
  printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
  maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
  timeBetweenShipments(timeBetweenShipments),
  truck(new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)) {
}

BottlingPlant::~BottlingPlant() {
  delete truck;
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
  return true; // TODO
}

void BottlingPlant::main() {
}
