#include <map>
#include <utility>

#ifndef PRINTER_H
#define PRINTER_H

_Monitor Printer {
  public:
    enum Kind {Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier};
    Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers);
    ~Printer();
    
    /* All print functions are intended to change the state of the specified actor, and possibly
     * set his extra values (if those were supplied in form of value1/value2). If the state of
     * the actor changed, print the updated states to display.
     */

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
    std::map<unsigned int, char> buffer; // Mapping from actor id to its current state
    std::map<unsigned int, std::pair<int, int> > extraValues; // Mapping from actor id
    // to the extra values we might have to store for it

    /* Each actor will be assigned a global id for the purpose of storing corresponding data.
     * Given the kind of actror and it's local id (if it exists), return it's unique id across
     * all actors.
     */
    unsigned int convertToGlobalId(Kind kind, unsigned int lid = 0);

    /* Print the row of current States for our actors, using info from buffer and extraValues
     */
    void displayStates();
  
    /* Print the special case of info row, where we indicate that particular task has finished execution
     */
    void displayFinishedState(unsigned int finishedId);
};

#endif //PRINTER_H_
