#ifndef WATCARD_H_
#define WATCARD_H_
#include <uFuture.h>

class WATCard {
    WATCard(const WATCard &);            // prevent copying
    WATCard &operator=(const WATCard &);

		unsigned int balance;
  public:
    WATCard();                              // Initialize watcard with $0 balance
    typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer
    void deposit(unsigned int amount);      // Add $amount to the watcard
    void withdraw(unsigned int amount);     // Withdraw $amount from the watcard
    unsigned int getBalance();              // The watcard balance in dollars
}; // WATCard

#endif //WATCARD_H_
