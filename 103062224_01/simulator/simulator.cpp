#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#include "./instruction.h"
#include "./regfile.h"
#include "./memory.h"

Memory* memory;
InstructionMemery* instructions;
Registers* regs;
unsigned int PC;

std::vector<unsigned int>* readImage(FILE *);
void readInput_initialize(void);
void print_snapshot(FILE *, int);
int execute(void);
void destroy_all(void);

int main(int argc, char const *argv[])
{
	/*printf("This is the main functuion in simulator.cpp\n");
	instruction();
	regfile();
	memory();*/
	readInput_initialize();
	//for(int i=0 ; i<instructions->size() ; i++)printf("%x ", instructions->at(i));
	//for(int i=0 ; i<regs->size() ; i++) printf("%x ", regs->at(i));
	//printf("\n") ;

	int cycle = 0;
	FILE *snapshot = fopen("snapshot.rpt", "w");
	if(snapshot==NULL){
		fputs("snapshot write error", stderr);
		exit(2);
	}
	print_snapshot(snapshot, cycle);
	while (execute() != -1){
		cycle++;
		print_snapshot(snapshot, cycle);
	}

	destroy_all();
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
	instructions = new InstructionMemery(PC, iimage);
	//for(unsigned int i=0 ; i<instructions->size() ; i++)	printf("%x\n", instructions->at(i));

	regs = new Registers(sp);
	//for(unsigned int i=0 ; i<regs->size() ; i++)	printf("%d: %x\n", i, regs->at(i));
	//printf("\n");
}

int execute(void)
{
	unsigned int inst = instructions->at(PC/4);
	PC += 4;
	//printf("inst==%x  ", inst);
	unsigned char opcode = (unsigned char) (inst >> 26);		//warning: unsigned char has 8 bits
	unsigned char rs =  (unsigned char) ( (inst >> 21) & 0x1f );
	unsigned char rt = (unsigned char) ( (inst >> 16) & 0x1f );
	unsigned char shamt = (unsigned char) ( (inst >> 6) & 0x1f );
	if(opcode == 0x00){
		unsigned char funct = (unsigned char) (inst & 0x3f);
		unsigned char rd = (unsigned char) ( (inst >> 11) & 0x1f );

		switch(funct)
		{
			case 0x20:	// add
				regs->at(rd) = regs->at(rs) + regs->at(rt) ;
				break;
			case 0x21:	// addu
				regs->at(rd) = (unsigned int)regs->at(rs) + (unsigned int)regs->at(rt);
				break;
			case 0x22:	// sub
				regs->at(rd) = regs->at(rs) - regs->at(rt);
				break;
			case 0x24:	// and
				regs->at(rd) = regs->at(rs) & regs->at(rt);
				break;
			case 0x25:	// or
				regs->at(rd) = regs->at(rs) | regs->at(rt);
				break;
			case 0x26:	//xor
				regs->at(rd) = regs->at(rs) ^ regs->at(rt);
				break;
			case 0x27:	//nor
				regs->at(rd) = ~(regs->at(rs) | regs->at(rt));
				break;
			case 0x28:	//nand
				regs->at(rd) = ~(regs->at(rs) & regs->at(rt));
				break;
			case 0x2a:	//slt
				regs->at(rd) = ( regs->at(rs) < regs->at(rt) ) ? 1:0;
				break;
			case 0x00:	//sll
				regs->at(rd) = regs->at(rt) << shamt;
				break;
			case 0x02:	//srl
				regs->at(rd) = ((unsigned int)regs->at(rt)) >> shamt;
				break;
			case 0x03:	//sra
				regs->at(rd) =regs->at(rt) >> shamt;
				break;
			case 0x08:	//jr
				PC = regs->at(rs);
				break;
			default: break;
		}
	} else {
		unsigned int immediate = inst & 0xffff;
		unsigned int address = inst & 0x3ffffff;
		switch(opcode)
		{
			case 0x08: 	// addi
				//printf("immediate==%d\n", immediate);
				regs->at(rt) = regs->at(rs) + immediate;
				break;
			case 0x3f:	// halt
				return -1;
				break;
			default:break;
		}
	}

	return 0;
}



void print_snapshot(FILE *snapshot, int cycle)
{
	fprintf(snapshot , "cycle %d\n", cycle);
	for(unsigned int i=0 ; i<regs->size() ; i++){
		fprintf(snapshot, "$%d: 0x%08x\n", i, (unsigned int)regs->at(i));
	}
	fprintf(snapshot, "\n\n");
}




void destroy_all(void)
{
	delete memory;
	delete instructions;
	delete regs;
}



/*
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
*/