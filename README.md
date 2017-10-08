# Advanced-Architecture 

ACA Simulator

## Instruction Set: CORG-V

| Opcode | Operands | Usage |
|:------:|:--------:|:------|
|IADD    | r0,r1,r2 | Add the integer contents of r1 and r2 and store in r0 |
|IADDI	 | r0,r1,v  | Add the integer contents of r1 and v and store in r0 |
|IMUL	 | r0,r1,r2 | Multiply the integer contents of r1 and r2 and store in r0 |
|IMULI   | r0,r1,v  | Multiply the integer contents of r1 and v and store in r0 |
|ICMP	 | r0,r1,r2 | Compare the integer contents of r1 and r2 and store -1 (r1<r2) 0 (r1=r2) or 1(r1>r2) in r0 |
|LD		 | r0,r1,v  | Load contents of address r1+v into r0 |
|LDI	 | r0,v		| Load v into r0 |
|STR	 | r0,r1,r2 | Store the contents of r2 in address r1+r0 |
|STRI	 | r0,v     | Store the contents of r0 in address v |
|BRA	 | v		| Branch to immediate address |
|JUM	 | v		| Relative branch to address |
|BLT	 | r0, r1, v| Relative branch to address if r0 < r1 |
|HALTEZ	 | r0		| Halt the program if r0 == 0 |
|HALTEQ  | r0,v		| Halt the program if r0 ==v |