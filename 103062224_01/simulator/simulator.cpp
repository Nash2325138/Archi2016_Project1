#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "./instruction.h"
#include "./regfile.h"
#include "./memory.h"

std::vector<unsigned int>* readImage(FILE *);

int main(int argc, char const *argv[])
{
	printf("This is the main functuion in simulator.cpp\n");
	instruction();
	regfile();
	memory();


	FILE *dimage = fopen("dimage.bin", "rb");
	if( dimage==NULL ) {
		fputs("dimage read error", stderr);
		exit(2);
	}
	std::vector<unsigned int> *dataInMemory = readImage(dimage);
	//for( std::vector<unsigned int>::iterator it = dataInMemory->begin() ; it != dataInMemory->end() ; it++ ) printf("%x ", *it);

	FILE *iimage = fopen("iimage.bin", "rb");
	if(iimage==NULL) {
		fputs("iimage read error", stderr);
		exit(2);
	}
	std::vector<unsigned int> *instructions = readImage(iimage);
	//for( std::vector<unsigned int>::iterator it = instructions->begin() ; it != instructions->end() ; it++ ) printf("%x ", *it);

	Register *regs = new Register();
	for(std::vector<unsigned int>::iterator it=regs->begin() ; it!=regs->end() ; it++){
		printf("%u ", *it);
	}

	return 0;
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