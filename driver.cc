#include <iostream>
#include <vector>
#include <unistd.h>

#include "config.h"
#include "printer.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "bottlingPlant.h"
#include "MPRNG.h"

using namespace std;

char* DEFAULT_CONFIG_FILE = "soda.config";

MPRNG randGen;

// Displays usage error message and quits the program with non-zero return code
void usageError() {
  osacquire(cout) << "Usage: ./soda_64 [ config-file [ random-seed (> 0) ] ]" << endl;
  exit(EXIT_FAILURE); // TERMINATE
}

// Convert argv[idx] into an integer, or quit if not possible
int readArgvNumber(char** argv, int idx) {
  int i = 0;
  while (argv[idx][i] != '\0') {
    if (!isdigit(argv[idx][i])) {
      usageError();
    }
    i++;
  }
  return atoi(argv[idx]);
}

void uMain::main() {
  if (argc >= 4) { // Invalid # of commad line arguments
    usageError();
  }

  ConfigParms configs;
  char* configFile = argc <= 1 ? DEFAULT_CONFIG_FILE : argv[1];
  processConfigFile(configFile, configs);

  int seed = argc <= 2 ? getpid() : readArgvNumber(argv, 2);

  // Uncomment to use more processors if there is a need.
  // uProcessor p[16] __attribute__((  ));

  // Set the random seed
  randGen.seed(seed);

  // Creation of objects starts here
  Printer *printer = new Printer(configs.numStudents, configs.numVendingMachines, configs.numCouriers);
  NameServer *nameServer = new NameServer(*printer, configs.numVendingMachines, configs.numStudents);

  vector<VendingMachine*> machines;
  for (size_t i = 0; i < configs.numVendingMachines; i++) {
    machines.push_back(new VendingMachine(*printer, *nameServer, i, configs.sodaCost, configs.maxStockPerFlavour));
  }

  BottlingPlant *plant = new BottlingPlant(*printer, *nameServer, configs.numVendingMachines,
      configs.maxShippedPerFlavour, configs.maxStockPerFlavour, configs.timeBetweenShipments);
  // Creation of objects ends here

  // Deletion of objects starts here

  // Delete students first - the system should be ready to close down when they did
  // all the purchases

  delete plant;
  for (size_t i = 0; i < configs.numVendingMachines; i++) {
    delete machines[i];
  }
  delete nameServer;
  delete printer;
  // Deletion of objects ends here
} // uMain::main
