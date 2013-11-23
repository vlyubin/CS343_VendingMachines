#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"

#ifndef TRUCK_H_
#define TRUCK_H_

_Task Truck {
    Printer &printer;
    NameServer &nameServer;
    BottlingPlant &plant;
    unsigned int numVendingMachines, maxStockPerFlavour;

    enum States {Starting = 'S', PickedUp = 'P', BeginDelivery = 'd', UnsuccessfullyFilled = 'U',
      EndDelivery = 'D', Finished = 'F'};
    void main();
  public:
    Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour);
};

#endif //TRUCK_H_
