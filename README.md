# Advanced-Architecture 

ACA Simulator

## Instruction Set: CORG-V

| Opcode | Operands | Usage |
|:------:|:--------:|:------|
|IADD    | r0,r1,r2 | Add the integer contents of r1 and r2 and store in r0 |
|IADDI	 | r0,r1,v  | Add the integer contents of r1 and v and store in r0 |
|ICMP	 | r0,r1,r2 | Compare the integer contents of r1 and r2 and store -1 (r1<r2) 0 (r1=r2) or 1(r1>r2) in r0 |
|LD		 | r0,r1,v  | Load contents of address r1+v into r0 |
|LDI	 | r0,v		| Load contents of address v into r0 |
|BRA	 | v		| Branch to immediate address |
|JUM	 | v		| Relative branch to address |
|BLT	 | r0, r1, v| Relative branch to address if r0 < r1 |