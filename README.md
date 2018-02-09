# Corgi Lake

Superscalar CPU simulator written in C++ featuring:
* Multiple execution units
* Out-of-Order execution
* Pipelining
* Dynamic branch prediction
* Register renaming
* Shelving
* Out-of-Order Load/Stores
* A rudimentary 'CorgiScript' compiler
* 3+ IPC!

# Build instructions
Compiled on linux with CMake and C++14. Execute test suite via 'benchmark_runner.cpp'

## Instruction Set: CORG-V

| Opcode | Operands | Usage |
|:------:|:--------:|:------|
|IADD    | r0,r1,r2 | Add the integer contents of r1 and r2 and store in r0 |
|IADDI	 | r0,r1,v  | Add the integer contents of r1 and v and store in r0 |
|AND	 | r0,r1,r2 | And the integer contents of r1 and v and store in r0 |
|NOT	 | r0,r1    | Not the integer contents of r1 and store in r0 |
|PRNT	 | r0       | print the integer contents of r0 |
|IMUL	 | r0,r1,r2 | Multiply the integer contents of r1 and r2 and store in r0 |
|IMULI   | r0,r1,v  | Multiply the integer contents of r1 and v and store in r0 |
|ISUB	 | r0,r1,r2 | Subtract the integer contents of r2 from r1 and store in r0 |
|ICMP	 | r0,r1,r2 | Compare the integer contents of r1 and r2 and store -1 (r1<r2) 0 (r1=r2) or 1(r1>r2) in r0 |
|LD		 | r0,r1,v  | Load contents of address r1+v into r0 |
|LDI	 | r0,v		| Load v into r0 |
|STR	 | r0,r1,r2 | Store the contents of r2 in address r1+r0 |
|STRI	 | r0,v     | Store the contents of r0 in address v |
|BRA	 | v		| Branch to immediate address |
|JUM	 | v		| Relative branch to address |
|BLT	 | r0, r1, v| Relative branch to address if r0 < r1 |
|JLT	 | r0, r1, v| Absolute branch to address if r0 < r1 |
|HALTEZ	 | r0		| Halt the program if r0 == 0 |
|HALTEQ  | r0,v		| Halt the program if r0 ==v |
