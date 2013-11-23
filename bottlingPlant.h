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
    Truck* truck;

    enum States {Starting = 'S', Generating = 'G', PickedUp = 'P', Finished = 'F'};
    void main();
  public:
    BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments);
    ~BottlingPlant();
    bool getShipment(unsigned int cargo[]);
};

#endif // BOTTLING_PLANT_H_
