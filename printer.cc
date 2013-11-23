#include <iostream>

#include "printer.h"

using namespace std;

// Useful constants
#define TAB '\t'
#define FINISHED_ME "F"
#define FINISHED_OTHER "..."
#define DELIMITER "*******"
#define FINAL_DELIMITER "***********************"
#define COMMA ','
#define NEG_INFINITY -2000000000
#define PARENT "Parent"
#define WATCARD_OFFICE "WATOff"
#define NAME_SERVER "Names"
#define TRUCK "Truck"
#define PLANT "Plant"
#define STUDENT "Stud"
#define VENDING_MACHINE "Mach"
#define COURIER "Cour"
#define NUM_SINGLE_ACTORS 5
#define FINISHED 'F'

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) :
    numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers),
    numActors(NUM_SINGLE_ACTORS + numStudents + numVendingMachines + numCouriers), numTerminated(0) {
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

unsigned int Printer::convertToGlobalId(Kind kind, unsigned int lid) {
  switch (kind) {
    case Student:
      return NUM_SINGLE_ACTORS + lid;
    case Vending:
      return NUM_SINGLE_ACTORS + numStudents + lid;
    case Courier:
      return NUM_SINGLE_ACTORS + numStudents + numVendingMachines + lid;
    default: // Kind represents one of single actors (parent, truck, etc.), so just use
             // its enum value
      return kind;
  }
}

void Printer::print(Kind kind, char state) {
  print(kind, 0, state, NEG_INFINITY, NEG_INFINITY); // Call more general version of print()
}

void Printer::print(Kind kind, char state, int value1) {
  print(kind, 0, state, value1, NEG_INFINITY); // Call more general version of print()
}

void Printer::print(Kind kind, char state, int value1, int value2) {
  print(kind, 0, state, value1, value2); // Call more general version of print()
}

void Printer::print(Kind kind, unsigned int lid, char state) {
  print(kind, lid, state, NEG_INFINITY, NEG_INFINITY); // Call more general version of print()
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1) {
  print(kind, lid, state, value1, NEG_INFINITY); // Call more general version of print()
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2) {
  unsigned int id = convertToGlobalId(kind, lid);

  // Handle display of state as finished
  if (state == FINISHED) {
    // If buffer is non-empty, display it's content and clear them
    if (buffer.size()) {
      displayStates();
      buffer.clear();
    }
    // Display state of id as finished using sspecial function
    displayFinishedState(id);
    return;
  }

  if (buffer.find(id) != buffer.end()) {
    // Some state will be owerriten. Flush the buffer.
    displayStates();
  }
  buffer[id] = state; // Save the new value in the buffer
  extraValues[id] = make_pair(value1, value2);
}

void Printer::displayStates() {
  unsigned int previousId = 0;
  for (map<unsigned int, char>::iterator it = buffer.begin(); it != buffer.end(); ++it) {
    // Print the tabs preceeding the status
    for (size_t i = 0; i < it->first - previousId; i++) {
      cout << TAB;
    }
    previousId = it->first;
    cout << it->second; // Printthe state

    if (extraValues[it->first].first != NEG_INFINITY) {
      // If the id we are printing has an extra value, print it 
      cout << extraValues[it->first].first;
    }
    if (extraValues[it->first].second != NEG_INFINITY) {
      // If the id we are printing has a second extra value, print it as well
      cout << COMMA << extraValues[it->first].second;
    }
  }
  cout << endl;

  buffer.clear(); // Flush the buffer after printing
}

void Printer::displayFinishedState(unsigned int finishedId) {
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
    // If all actors terminated, print termination message
    cout << FINAL_DELIMITER << endl;
  }
}
