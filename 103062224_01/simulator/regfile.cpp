#include "regfile.h"
#include <cstdio>

void regfile(void)
{
	printf("This is regfile() in regfile.cpp\n");
}


Register::Register(void)
{
	this->resize(32);
	for(std::vector<unsigned int>::iterator it=this->begin() ; it!=this->end() ; it++) *it = 0;
}