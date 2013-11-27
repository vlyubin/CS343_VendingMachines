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
  printer.print(Printer::BottlingPlant, Finished); // Truck has to finish first
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
  if (isClosingDown) {
    return true;
  }

  for (size_t i = 0; i < NUM_FLAVOURS; i++) {
    cargo[i] = generatedStock[i]; // Whatever quantities were in cargo before are thrown away as those
    // soda cans are outdated now
  }
  printer.print(Printer::BottlingPlant, PickedUp);

  return false; // Plant is not closing down
}

void BottlingPlant::main() {
  printer.print(Printer::BottlingPlant, Starting);

  while (true) {
    yield(timeBetweenShipments);

    int totalBottlesCreated = 0;
    for (size_t i = 0; i < NUM_FLAVOURS; i++) {
      generatedStock[i] = randGen(maxShippedPerFlavour);
      totalBottlesCreated += generatedStock[i];
    }
    printer.print(Printer::BottlingPlant, Generating, totalBottlesCreated);

    _Accept(getShipment) {
    } or _Accept(~BottlingPlant) {
      isClosingDown = true;
      break;
    }
  }
}
