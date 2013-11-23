#include "watcard.h"
#include <cassert>

WATCard::WATCard(): balance(0) {}

WATCard::WATCard( const WATCard& watcard )
	:balance( watcard.balance ) {
}

WATCard& WATCard::operator=( const WATCard& watcard ) {
	balance = watcard.balance;
	return *this;
}

void WATCard::deposit( unsigned int amount ) {
	balance += amount;
}

void WATCard::withdraw( unsigned int amount ) {
	assert( balance >= amount );
	balance -= amount;
}

unsigned int WATCard::getBalance() {
	return balance;
}
