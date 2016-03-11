#include <cstdio>
#include "instruction.h"
#include "regfile.h"
#include "memory.h"

int main(int argc, char const *argv[])
{
	printf("This is the main functuion in simulator.cpp\n");
	instruction();
	regfile();
	memory();
	return 0;
}
