#include <iostream>

#include "printer.h"

using namespace std;

#define TAB '\t'
#define FINISHED_ME "F"
#define FINISHED_OTHER "..."
#define DELIMITER "*******"
#define FINAL_DELIMITER "***********************"
#define COMMA ','
#define INFINITY 2000000000
#define PARENT "Parent"
#define WATCARD_OFFICE "WATOff"
#define NAME_SERVER "Names"
#define TRUCK "Truck"
#define PLANT "Plant"
#define STUDENT "Stud"
#define VENDING_MACHINE "Mach"
#define COURIER "Cour"

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) :
    numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers),
    numActors(5 + numStudents + numVendingMachines + numCouriers), numTerminated(0) {
  // Print the column headings
  cout << PARENT << TAB << WATCARD_OFFICE << TAB << NAME_SERVER << TAB << TRUCK << TAB << PLANT;
  for (unsigned int i = 0; i < numStudents; i++) {
    cout << TAB << STUDENT << i;
  }
  for (unsigned int i = 0; i < numVendingMachines; i++) {
    cout << TAB << VENDING_MACHINE << i;
  }
  for (unsigned int i = 0; i < numCouriers; i++) {
    cout << TAB << COURIER << i;
  }

  // Print a row full of delimiters
  cout << endl << DELIMITER;
  for (unsigned int i = 1; i < numActors; i++) {
    cout << TAB << DELIMITER;
  }
  cout << endl;
}

void Printer::print(Kind kind, char state) {

}

void Printer::print(Kind kind, char state, int value1) {

}

void Printer::print(Kind kind, char state, int value1, int value2) {

}

void Printer::print(Kind kind, unsigned int lid, char state) {

}

void Printer::print(Kind kind, unsigned int lid, char state, int value1) {

}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2) {

}

void Printer::displayStates() {
  // TODO
}

void Printer::displayFinishedState(int finishedId) {
  numTerminated++;
  for (unsigned int i = 0; i < numActors; i++) {
    if (i) { // Print the tab for every entry, but first
      cout << TAB;
    }
    // Display different symbol for finished actor and everyone else
    cout << ((i == finishedId) ? FINISHED_ME : FINISHED_OTHER);
  }
  cout << endl;
  if (numTerminated == numActors) {
    // If all phisolophers terminated, print termination message
    cout << FINAL_DELIMITER << endl << "Philosophers terminated" << endl;
  }
}
