#define STACK_SIZE  4096   // desired stack size in bytes (including the stack guardband)

.section non_eds_stack, stack, address(0x8000 - 4096) ; allocate the stack below 0x8000
.space 4096

