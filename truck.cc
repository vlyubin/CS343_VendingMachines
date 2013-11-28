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
    yield(randGen(1, 10)); // Yield corresponding to getting coffee
    bool plantClosingDown = plant.getShipment(cargo);

    if (plantClosingDown) {
      // If plant is closing down, we can quit
      break;
    }

    // Calculate the total shipment amount
    int totalShipment = 0;
    for (size_t i = 0; i < NUM_FLAVOURS; i++) {
      totalShipment += cargo[i];
    }
    printer.print(Printer::Truck, PickedUp, totalShipment);

    for (size_t i = 0; i < numVendingMachines; i++) {
      // Start restocking vending machine i
      printer.print(Printer::Truck, BeginDelivery, (int)machines[i]->getId(), totalShipment);
      unsigned int* machineInventory = machines[i]->inventory();

      int emptySlotsLeft = 0; // How many empty slots will be left after delivery
      for (size_t j = 0; j < NUM_FLAVOURS; j++) {
        // We cannot add more than we have, nore we can add more than VM can contain
        unsigned int cansToAdd = min(maxStockPerFlavour - machineInventory[j], cargo[j]);

        // Restock cansToAdd cans
        machineInventory[j] += cansToAdd;
        cargo[j] -= cansToAdd;
        totalShipment -= cansToAdd; // Update the shipment amount we have left

        emptySlotsLeft += maxStockPerFlavour - machineInventory[j];
      }

      if (emptySlotsLeft) {
        // There were empty slots left, so delivery is unsuccessfull
        printer.print(Printer::Truck, UnsuccessfullyFilled, (int)machines[i]->getId(), emptySlotsLeft);
      }

      machines[i]->restocked(); // Indicate to VM that restocking is finished
      printer.print(Printer::Truck, EndDelivery, (int)machines[i]->getId(), totalShipment);
    }
  }

  printer.print(Printer::Truck, Finished);
}
