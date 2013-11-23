#include "printer.h"
#include "nameServer.h"

#ifndef BOTTLING_PLANT_H_
#define BOTTLING_PLANT_H_

_Task BottlingPlant {
    Printer &printer;
    NameServer &nameServer;
    unsigned int numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments;

    enum States {Starting = 'S', Generating = 'G', PickedUp = 'P', Finished = 'F'};
    void main();
  public:
    BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments);
    bool getShipment(unsigned int cargo[]);
};

#endif // BOTTLING_PLANT_H_
