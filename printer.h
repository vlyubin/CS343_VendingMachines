#include <map>

#ifndef PRINTER_H
#define PRINTER_H

_Monitor Printer {
  public:
    enum Kind {Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier};
    Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers);
    void print(Kind kind, char state);
    void print(Kind kind, char state, int value1);
    void print(Kind kind, char state, int value1, int value2);
    void print(Kind kind, unsigned int lid, char state);
    void print(Kind kind, unsigned int lid, char state, int value1);
    void print(Kind kind, unsigned int lid, char state, int value1, int value2);
  private:
  	unsigned int numStudents;
  	unsigned int numVendingMachines;
  	unsigned int numCouriers;
    unsigned int numActors; // Total number of actors in the process
    unsigned int numTerminated; // Total number of actors terminated
    std::map<unsigned int, char> buffer; // Mapping from actor id to its current state
    std::map<unsigned int, std::pair<unsigned int, unsigned int> > extraValues;

    unsigned int convertToGlobalId(Kind kind, unsigned int lid);

    /* Print the row of current States for our actors, using info from buffer and extraValues
     */
    void displayStates();
  
    /* Print the special case of info row, where we indicate that particular task has finished execution
     */
    void displayFinishedState(int finishedId);
};

#endif
