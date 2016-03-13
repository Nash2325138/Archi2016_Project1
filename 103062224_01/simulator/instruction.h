#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <cstdio>
#include <cstdlib>

void instruction_function(void);

class InstructionMemery : public std::vector<unsigned int>
{
public:
	InstructionMemery(FILE *iimage);
};

#endif
