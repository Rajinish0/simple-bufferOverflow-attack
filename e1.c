#include <stdio.h>

/*
So what's happening here is that when function is called
first c, b a are put on to the stack
and then
call function line basically just puts
rip (instruction pointer) on to the stack
and moves the ip of the function to rip

so the stack has smth like
[ ret ip ] [a] [b] [c]

then we push main's frame pointer onto the stack to be able
to restore it later, it's in rbp

push rbp
and we make this new top of the stack pointer the new
frame pointer

in other words 
mov rbp, rsp (intel syntax)

so the stack will have something like
[ return-rbp ] [return-rip] [a] [b] [c]

and then storage for buffer1 and buffer2

what i want to do is change the [return-rip]
so that the command x=1 is never exectued. 

But how??

Had to debug in gdb
i m not sure why but the stack looks like this
[buffer1 5 bytes] [int * ret 8 bytes] [stored-rbp] [stored-rip]
so from buffer1 i have to jump 5 + 8 + 8 bytes to get to rip

x=1 instruction was 7 bytes on assembly, so I just skip to the
next one
*/

void function(int a, int b, int c){
	char buffer1[5];
	char buffer2[10];
	int *ret;

	ret = (int*)(buffer1 + 5 + 8 + 8);
	(*ret) += 7;
}

void main(){
	int x;

	x = 0;
	function(1, 2, 3);
	x = 1;
	printf("%d\n", x);
}
