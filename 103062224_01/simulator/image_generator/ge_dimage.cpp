#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <ctype.h>

int main(){
	char Num[20];
	unsigned char c;
	int a, b;
	FILE *data = fopen("data.txt", "r");
	FILE *dimage = fopen("dimage.bin", "wb");
	while(fscanf(data, "%s", Num)!=EOF){
		if(isdigit(Num[0])) a = Num[0] - '0';
		else a = Num[0] - 'A' + 10;
		if(isdigit(Num[1])) b = Num[1] - '0';
		else b = Num[1] - 'A' + 10;
		c = a*16 + b;
		fwrite(&c, sizeof(unsigned char), 1, dimage);
		if(isdigit(Num[2])) a = Num[2] - '0';
		else a = Num[2] - 'A' + 10;
		if(isdigit(Num[3])) b = Num[3] - '0';
		else b = Num[3] - 'A' + 10;
		c = a*16 + b;
		fwrite(&c, sizeof(unsigned char), 1, dimage);
	}
	return 0;
}