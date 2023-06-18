Stack_Size    	EQU   	0x400
bottom_of_stack   EQU 	0x20000000
top_of_stack  	EQU 	bottom_of_stack + Stack_Size
b				EQU		0xff000000
a				EQU		0x00000000
c				EQU		0xf0000000
x				EQU		0xFF7FF7F8
  AREA	RESET,	DATA, READONLY
  DCD   top_of_stack  
  DCD   Start
  AREA  MY_CODE, CODE, READONLY 
  ENTRY
Start    PROC
	;1 part lr
	LDR R0,=a
	LDR R1,=b
	LDR R2,=c
	MOV R4,#2
	UDIV R2,R4
	SUB R1,R0
	UMLAL R2,R3,R1,R4	
	;2 part lr
	LDR R0,=x
	AND R0,#0x3FFFFFFF
	ORR R0,#0x3
	ROR R0,#30
	NOP
	ENDP
	END
