# All files must be compiled using -fno-stack-protector flag


# INSTRUCTIONS FOR GETTING THE SHELLCODE in e2.c

I opened ./shell in gdb, shell.c was compiled using -static flag
so i had excess to __execve function's assembly code in gdb
from the code it could be deduced what arguments the execve function takes and
in what order and through which registers, plus what is the syscall number for execve.

For safe exit, syscall to exit must also be called in case execve fails.

The assembly code is in shellAssem.c (with comments), to get the byte representation I opened ./shellAssem in gdb and just did `x/bx main+8`...
or `x/60bx main+8`

# INSTRUCTIONS FOR RUNNING ./e2

Unfortunately, ./e2 cannot be run directly. The problem is that the shellcode (array of chars) is stored in the chunk of memory that is not executable, so what I did was run ./e2 in gdb and as soon as ret was called from main it redirected to shellcode but before that was executed I executed the following commands

`info proc mappings` - to see where exactly the shellcode lies, and what it's permissions are. There was no 'x' property.

The following command then must be run in gdb to give it that property

`call (int)mprotect(MEMORY_ADDR, SIZE_OF_MEMORY, 1 | 2 | 4)`

(1, 2, 4) are READ, WRITE, EXECUTE flags 
SIZE_OF_MEMORY for my device was 0x1000 or 4096.
MEMORY_ADDR should be looked using the command 'info proc mappings'

Also, 'si' should be used instead of 'ni' while executing the shellcode in gdb.

To check if call to mprotect was correct do 'info proc mappings' again to see the properties of that memory chunk, and then continue executing the code using 'si'.


