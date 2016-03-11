ALL_OBJ = simulator.o instruction.o regfile.o memory.o
simulator: ${ALL_OBJ}
	g++ -o simulator ${ALL_OBJ}
allObj: ./*cpp
	g++ -Wall -c ./*.cpp
simulator.o: simulator.cpp
	g++ -Wall -c simulator.cpp
instruction.o: instruction.cpp
	g++ -Wall -c instruction.cpp
regfile.o: regfile.cpp
	g++ -Wall -c regfile.cpp
memory.o: memory.cpp
	g++ -Wall -c memory.cpp
clean:
	rm -f simulator ${ALL_OBJ}
