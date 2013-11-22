#ifndef BOTTLING_PLANT_H_
#define BOTTLING_PLANT_H_

_Task BottlingPlant {
    void main();
  public:
    BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments);
    bool getShipment(unsigned int cargo[]);
};

#endif // BOTTLING_PLANT_H_
