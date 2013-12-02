#ifndef TRUCK_H_
#define TRUCK_H_

_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {
    Printer &printer;
    NameServer &nameServer;
    BottlingPlant &plant;
    const unsigned int numVendingMachines;
    const unsigned int maxStockPerFlavour;

    // States we can print for Truck
    enum States {Starting = 'S', PickedUp = 'P', BeginDelivery = 'd', UnsuccessfullyFilled = 'U',
      EndDelivery = 'D', Finished = 'F'};
    void main();
  public:
    Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour);
}; // Truck

#endif //TRUCK_H_
