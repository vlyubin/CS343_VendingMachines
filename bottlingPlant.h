#include "printer.h"
#include "nameServer.h"

#define NUM_FLAVOURS 4

_Task Truck;

#ifndef BOTTLING_PLANT_H_
#define BOTTLING_PLANT_H_

_Task BottlingPlant {
    Printer &printer;
    NameServer &nameServer;
    unsigned int numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments;
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
};

#endif // BOTTLING_PLANT_H_
