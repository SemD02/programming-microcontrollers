Stack_Size    	EQU   	0x400
bottom_of_stack   EQU 	0x20000000
top_of_stack  	EQU 	bottom_of_stack + Stack_Size
;a				EQU		0x00000000
;b				EQU		0xff000000
;c				EQU		0xf0000000
a				EQU		3
b				EQU		1
c				EQU		-3
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
	CMP R0,#2
	BNE else1
	CMP R1,#1
	BNE else1
	CMP R2,#-3
	BNE else1
	
	MOV R4,#2
	UDIV R2,R4
	SUB R1,R0
	UMLAL R2,R3,R1,R4
	B part1_end
else1
	MOV R3,#1
part1_end
	;2 part lr	
	;R0 is a
	MOV R1,#2
	MOV R4,#0
loop
	CMP R1,#14
	BHI end_cycle
	ORR R2,R0,R1
	ADD R4, R2
	ADD R4, #8
	ADD R1,#1
	B loop
end_cycle
	NOP
	ENDP
	END
