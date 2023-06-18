Stack_Size    	EQU   	0x400
bottom_of_stack   EQU 	0x20000000
top_of_stack  	EQU 	bottom_of_stack + Stack_Size
a				EQU		0x0000F000
  AREA	RESET,	DATA, READONLY
  DCD   top_of_stack  
  DCD   Start
Reset_Handler
zero			RN 		R10
one				RN 		R11
temp			RN		R9
  AREA MyArray, DATA, READONLY
	DCD 0x11111111 , 0x22222222 , 0x33333333 , 0x44444444 , 0x55555555 , 0x66666666, 0x77777777, 0x88888888, 0x99999999,0xAAAAAAAA   
  AREA  MY_CODE, CODE, READONLY 
  ENTRY
Start    PROC
	LDR zero,=0
	LDR one,=1	
	;work part
	LDR R0,=MyArray
	LDR R3,=0x200001B0
	LDR R2,=10
loop1
	LDR temp,[R0],#4	
	STR temp,[R3],#4
	SUBS R2,one
	CMP R2,zero
	BNE loop1
	;for new loop
	LDR R3,=0x200001B0
	LDR R2,=5
loop2
	LDR temp,[R3,#4]
	LDR R1,[R3]
	PUSH {temp}
	PUSH {R1}
	STR temp,[R3],#4
	STR R1,[R3],#4
	SUBS R2,one
	CMP R2,zero
	BNE loop2	
	;for new loop
	LDR R3,=0x200001B0
	LDR R2,=10
	;
loop3
	POP {temp}
	STR temp,[R3],#4
	SUBS R2,one
	CMP R2,zero
	BNE loop3	
	
	NOP
	ENDP
	END
