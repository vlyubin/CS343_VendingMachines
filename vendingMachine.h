#include "printer.h"
#include "nameServer.h"
#include "watcard.h"

#define NUM_FLAVOURS 4

#ifndef VENDING_MACHINE_H_
#define VENDING_MACHINE_H_

_Task VendingMachine {
    Printer &printer;
    NameServer &nameServer;
    unsigned int id, sodaCost, maxStockPerFlavour;
    unsigned int* soda; // Soda that this VM contains. NUM_FLAVOURS

    // States we can print for Truck
    enum States {Starting = 'S', StartReloading = 'r', CompleteReloading = 'R', Bought = 'B', Finished = 'F'};
    void main();
  public:
    enum Flavours {ORANGE, COLA, GRAPE, CHERRY}; // flavours of soda
    enum Status {BUY, STOCK, FUNDS};     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour);
    ~VendingMachine();
    Status buy(Flavours flavour, WATCard &card);
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif //VENDING_MACHINE_H_
