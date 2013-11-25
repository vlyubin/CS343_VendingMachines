#include "bottlingPlant.h"
#include "truck.h"
#include "MPRNG.h"

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
  printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
  maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
  timeBetweenShipments(timeBetweenShipments), isClosingDown(false),
  truck(new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)) {
}

BottlingPlant::~BottlingPlant() {
  delete truck;
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
  if (isClosingDown) {
    return true;
  }

  for (size_t i = 0; i < NUM_FLAVOURS; i++) {
    cargo[i] = generatedStock[i]; // Whatever quantities were in cargo before are thrown away as those
    // soda cans are outdated now
  }
  return false; // Plant is not closing down
}

void BottlingPlant::main() {
  while (true) {
    yield(timeBetweenShipments);

    for (size_t i = 0; i < NUM_FLAVOURS; i++) {
      generatedStock[i] = randGen(maxShippedPerFlavour);
    }

    _Accept(getShipment) {
    } or _Accept(~BottlingPlant) {
      isClosingDown = true;
      break;
    }
  }
}
