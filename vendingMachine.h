#ifndef VENDING_MACHINE_H_
#define VENDING_MACHINE_H_

_Monitor Printer;
class WATCard;
_Task NameServer;

_Task VendingMachine {
    Printer &printer;
    NameServer &nameServer;
    const unsigned int id;
    const unsigned int sodaCost;
    const unsigned int maxStockPerFlavour;
    unsigned int* soda; // Soda that this VM contains. It has NUM_FLAVOURS entries, representing counts
    // for each flavour

    // States we can print for VendingMachine
    enum States {Starting = 'S', StartReloading = 'r', CompleteReloading = 'R', Bought = 'B', Finished = 'F'};
    void main();
  public:
    enum Flavours {ORANGE, COLA, GRAPE, CHERRY}; // flavours of soda
    enum Status {BUY, STOCK, FUNDS};     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour);
    ~VendingMachine();
    Status buy(Flavours flavour, WATCard &card); // Buy a soda of flavour flavour using watcard card. It can
    // return any Status, depending on situation
    unsigned int *inventory(); // Truck calls this when starting restocking. We return a pointer to our soda array
    void restocked(); // Truck calls this to indicate that restocking is finished

    // Getters for private fields of the class
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
}; // VendingMachine

#endif //VENDING_MACHINE_H_
