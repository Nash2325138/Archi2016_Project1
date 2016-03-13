#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "./instruction.h"
#include "./regfile.h"
#include "./memory.h"


Memory* memory;
InstructionMemery* instructions;
Registers* regs;
unsigned int PC;

std::vector<unsigned int>* readImage(FILE *);
void readInput_initialize(void);

int main(int argc, char const *argv[])
{
	/*printf("This is the main functuion in simulator.cpp\n");
	instruction();
	regfile();
	memory();*/
	readInput_initialize();

	return 0;
}

void readInput_initialize(void)
{
	FILE *dimage = fopen("dimage.bin", "rb");
	if( dimage==NULL ) {
		fputs("dimage read error", stderr);
		exit(2);
	}
	unsigned int sp=0;
	unsigned char readByte;
	for(int i=0 ; i<4 ; i++){
		fread(&readByte, sizeof(unsigned char), 1, dimage);
		sp <<= 8;
		sp |= readByte;
	}
	memory = new Memory(dimage);
	//for(unsigned int i=0 ; i<memory->size() ; i++)	printf("%x\n", memory->at(i));

	
	FILE *iimage = fopen("iimage.bin", "rb");
	if(iimage==NULL) {
		fputs("iimage read error", stderr);
		exit(2);
	}
	PC = 0;
	for(int i=0 ; i<4; i++){
		fread(&readByte, sizeof(unsigned char), 1, iimage);
		PC <<= 8;
		PC |= readByte;
	}
	instructions = new InstructionMemery(iimage);
	//for(unsigned int i=0 ; i<instructions->size() ; i++)	printf("%x\n", instructions->at(i));

	regs = new Registers(sp);
	//for(unsigned int i=0 ; i<regs->size() ; i++)	printf("%d: %x\n", i, regs->at(i));
}

std::vector<unsigned int>* readImage(FILE *image)
{
	std::vector<unsigned int> *input = new std::vector<unsigned int>;
	input->reserve(256);
	unsigned char readByte;
	unsigned int count=0, temp=0;
	while(fread(&readByte, sizeof(unsigned char), 1, image) != 0){
		temp <<= 8;
		temp |= readByte;
		count++;
		if(count >= 4){
			input->push_back(temp);
			temp = count = 0;	
		}
	}
	//printf("input has %lu words\n", input->size()) ;
	return input;
}