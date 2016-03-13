#include <cstdio>
#include <cstdlib>
#include <map>
#include <string.h>
void write_32bits_to_image(FILE *image, unsigned int instruction);


int main(int argc, char const *argv[])
{
	FILE *assembly = fopen("assembly.txt", "r");
	FILE *iimage = fopen("iimage.bin", "wb");
	//fwrite(&my_record, sizeof(struct rec), 1, ptr_myfile);
	unsigned int PC;
	unsigned int num_inst;
	fscanf(assembly, "%u %u", &PC, &num_inst);
	write_32bits_to_image(iimage, PC);
	write_32bits_to_image(iimage, num_inst);


	char type[5];
	char inst[10];
	int count=0;
	while( fscanf(assembly, " %s %s", type, inst) == 2 )
	{
		count++;
		if(count > num_inst) printf("\n Number of instruction exceed what you said !!\n");
		printf("%s %s ", type, inst);
		unsigned int instruction=0;
		if(strcmp(type, "R")==0)
		{
			instruction <<= 6;
			instruction |= 0x00;
			unsigned int rd, rs, rt;
			if( fscanf(assembly, " $%u, $%u, $%u", &rd, &rs, &rt)==0 ) exit(99);
			printf(" $%u, $%u, $%u  ", rd, rs, rt);
			instruction <<= 5;
			instruction |= rs;

			instruction <<= 5;
			instruction |= rt;

			instruction <<= 5;
			instruction |= rd;

			instruction <<= 5;	// shamt doesn't bother

			instruction <<= 6;
			if(strcmp(inst, "add")==0)		instruction |= 0x20;
			else if(strcmp(inst, "addu")==0) 	instruction |= 0x21;
			else if(strcmp(inst, "sub")==0) 	instruction |= 0x22;

		}
		else if(strcmp(type, "R_shift")==0)
		{

		}
		else if(strcmp(type, "R_jr")==0)
		{

		}
		else if(strcmp(type, "I")==0)
		{
			unsigned int rs, rt;
			short immediate;
			if(fscanf(assembly, " $%u, $%u, %hd", &rt, &rs, &immediate)==0) exit(99);	//%hd to read short decimal
			printf("$%u, $%u, %hd   ", rt, rs, immediate);
			if(strcmp(inst, "addi")==0) instruction |= 0x08;
			else{}
			instruction <<= 5;
			instruction |= rs;

			instruction <<= 5;
			instruction |= rt;

			instruction <<= 16;
			instruction |= immediate;
		}
		else if(strcmp(type, "LUI")==0)
		{

		}
		else if(strcmp(type, "BGTZ")==0)
		{

		}
		else if(strcmp(type, "J")==0)
		{

		}
		else if(strcmp(type, "S")==0)
		{
			if(strcmp(inst, "halt")==0){
				instruction |= 0xffffffff;
			}
		}
		printf("%08x\n", instruction);
		write_32bits_to_image(iimage, instruction);
	}
	//for(int i=0 ; i<5 ; i++) write_32bits_to_image(iimage, 0xffffffff);	// write halt to the end of .bin
	fclose(iimage);
	return 0;
}

void write_32bits_to_image(FILE *image, unsigned int number)
{
	for(int i=0 ; i<4 ; i++){
		unsigned char temp = (unsigned char)(number >> 24);
		fwrite(&temp, sizeof(unsigned char), 1, image);
		number <<= 8;
	}
}