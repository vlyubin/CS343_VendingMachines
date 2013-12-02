#ifndef BOTTLING_PLANT_H_
#define BOTTLING_PLANT_H_
#include "constants.h"

_Task Truck;
_Task NameServer;
_Monitor Printer;

_Task BottlingPlant {
    Printer &printer;
    NameServer &nameServer;
    const unsigned int numVendingMachines;
    const unsigned int maxShippedPerFlavour;
    const unsigned int maxStockPerFlavour;
    const unsigned int timeBetweenShipments;
    bool isClosingDown; // True if plant is closed now, false otherwise
    Truck* truck;
    unsigned int generatedStock[NUM_FLAVOURS]; // Quantity of stock that we generated for each flavour

    // States we can print for BottlingPlant
    enum States {Starting = 'S', Generating = 'G', PickedUp = 'P', Finished = 'F'};
    void main();
  public:
    BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments);
    ~BottlingPlant();
    bool getShipment(unsigned int cargo[]); // Returns true if plant is closed now. Otherwise,
    // it returns false and fills cargo with generatedStock values
}; // BottlingPlant

#endif // BOTTLING_PLANT_H_
