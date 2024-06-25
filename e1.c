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

word size is 4 bytes
buffer1 is therefore stored as 2 words
so 8 bytes, frame buffer is 4 bytes
so 12 bytes of jump from buffer1 is required
to reach [return-rip]
*/

void function(int a, int b, int c){
	char buffer1[5];
	char buffer2[10];

	int *ret;
	/*
	ret = buffer1 + 16;
	(*ret) += 16;
	*/

	ret = buffer1 + 12;
	(*ret) += 8;
}

void main(){
	int x;

	x = 0;
	function(1, 2, 3);
	x = 1;
	printf("%d\n", x);
}
