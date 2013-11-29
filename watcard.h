#ifndef WATCARD_H_
#define WATCARD_H_
#include <uFuture.h>

class WATCard {
    WATCard(const WATCard &);            // prevent copying
    WATCard &operator=(const WATCard &);

		unsigned int balance;
  public:
    WATCard();
    typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer
    void deposit(unsigned int amount);
    void withdraw(unsigned int amount);
    unsigned int getBalance();
};

#endif //WATCARD_H_
