#include "parent.h"
#include "MPRNG.h"
#include "bank.h"

void Parent::main() {
	while (true) {
		_Accept( ~Parent ) {
			break;
		} _Else {
			yield( parentalDelay );
			unsigned int studentID = randGen( numStudents - 1 );
			unsigned int amount = randGen( 1, 3 );
			bank.deposit( studentID, amount );
		}
	}
}

Parent::Parent( Printer& prt, Bank& bank, unsigned int numStudents,
		unsigned int parentalDelay )
		: printer( prt ), bank( bank ), numStudents( numStudents ),
		  parentalDelay( parentalDelay ) {
}
