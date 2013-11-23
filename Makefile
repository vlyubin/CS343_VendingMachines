CXX = u++						# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -Wno-unused-local-typedefs -MMD ${OPT} -DTYPE="${TYPE}" # compiler flags

OBJECTS = driver.o bank.o bottlingPlant.o config.o nameServer.o parent.o \
          printer.o student.o truck.o vendingMachine.o watcard.o watcardOffice.o
EXECS = soda
DEPENDS = ${OBJECTS:.o=.d}				# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXECS}						# build all executables

${EXECS} : ${OBJECTS}					# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

-include ${DEPENDS}					# include *.d files containing program dependences

clean :							# remove files that can be regenerated
	rm -f *.d *.o ${EXECS}
