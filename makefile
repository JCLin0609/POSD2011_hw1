INC_DIR = include

all: main

main: main.o LogicSimulator.o device.o TextUI.o
ifeq (${OS}, Windows_NT)
	g++ -o hw1 main.o LogicSimulator.o device.o TextUI.o -lgtest
else
	g++ -o hw1 main.o LogicSimulator.o device.o TextUI.o -lgtest -lpthread
endif
	
main.o: main.cpp 
	g++ -std=gnu++0x -c main.cpp
LogicSimulator.o: $(INC_DIR)/LogicSimulator.h LogicSimulator.cpp
	g++ -std=gnu++0x -c LogicSimulator.cpp
device.o: $(INC_DIR)/device.h device.cpp
	g++ -std=gnu++0x -c device.cpp
TextUI.o: $(INC_DIR)/TextUI.h TextUI.cpp
	g++ -std=gnu++0x -c TextUI.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o main
endif
