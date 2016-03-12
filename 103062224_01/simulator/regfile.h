#ifndef REGFILE_H
#define REGFILE_H

#include <vector>
class Register : public std::vector< unsigned int >
{
public:
	Register(void);
};

void regfile(void);

#endif