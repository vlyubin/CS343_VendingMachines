#include "truck.h"
#include "MPRNG.h"

using namespace std;

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
    unsigned int numVendingMachines, unsigned int maxStockPerFlavour) : printer(prt),
  nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines),
  maxStockPerFlavour(maxStockPerFlavour) {
}

void Truck::main() {
  unsigned int cargo[NUM_FLAVOURS];

  while (1) {
    yield(randGen(1, 10));
    bool plantClosingDown = plant.getShipment(cargo);

    if (plantClosingDown) {
      break;
    }

  }
}
