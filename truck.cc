#include "truck.h"
#include "vendingMachine.h"
#include "MPRNG.h"

using namespace std;

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
    unsigned int numVendingMachines, unsigned int maxStockPerFlavour) : printer(prt),
  nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines),
  maxStockPerFlavour(maxStockPerFlavour) {
}

void Truck::main() {
  printer.print(Printer::Truck, Starting);

  unsigned int cargo[NUM_FLAVOURS];
  VendingMachine** machines = nameServer.getMachineList();

  while (1) {
    yield(randGen(1, 10));
    bool plantClosingDown = plant.getShipment(cargo);

    if (plantClosingDown) {
      break;
    }

    int totalShipment = 0;
    for (size_t i = 0; i < NUM_FLAVOURS; i++) {
      totalShipment += cargo[i];
    }
    printer.print(Printer::Truck, PickedUp, totalShipment);

    for (size_t i = 0; i < numVendingMachines; i++) {
      unsigned int* machineInventory = machines[i]->inventory();

      for (size_t j = 0; j < NUM_FLAVOURS; j++) {
        unsigned int cansToAdd = min(maxStockPerFlavour - machineInventory[j], cargo[j]);
        machineInventory[j] += cansToAdd;
        cargo[j] -= cansToAdd;
      }

      machines[i]->restocked();
    }
  }

  printer.print(Printer::Truck, Finished);
}
