Stack_Size    	EQU   	0x400
bottom_of_stack   EQU 	0x20000000
top_of_stack  	EQU 	bottom_of_stack + Stack_Size
my_constant		EQU		3949494555
clear 			equ 	0xFFFFFF00
  AREA	RESET,	DATA, READONLY
  DCD   top_of_stack  
  DCD   Start
  AREA  MY_CODE, CODE, READONLY 
  ENTRY
Start    PROC
  LDR R0, =my_constant
  STR R0, [R13, #0] 
  LDR R1, [R13, #3]
  LDR R2, [R13, #2]
  LDR R3, [R13, #1]
  LDR R4, [R13, #0]
  LDR R5, =clear
  BIC R2,R5
  BIC R3,R5
  BIC R4,R5
  ENDP
  END
