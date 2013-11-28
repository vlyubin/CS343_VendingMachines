#include "parent.h"
#include "bank.h"
#include "MPRNG.h"
#include "printer.h"

void Parent::main() {
	printer.print( Printer::Parent, 'S' );
	while (true) {
		_Accept( ~Parent ) {
			break;
		} _Else {
			yield( parentalDelay );
			unsigned int studentID = randGen( numStudents - 1 );
			unsigned int amount = randGen( 1, 3 );
			bank.deposit( studentID, amount );
			printer.print( Printer::Parent, 'D', studentID, amount );
		}
	}
	printer.print( Printer::Parent, 'F' );
}

Parent::Parent( Printer& prt, Bank& bank, unsigned int numStudents,
		unsigned int parentalDelay )
		: printer( prt ), bank( bank ), numStudents( numStudents ),
		  parentalDelay( parentalDelay ) {
}
