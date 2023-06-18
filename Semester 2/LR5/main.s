Stack_Size EQU 0x400
bottom_of_stack EQU 0x20000000
top_of_stack EQU bottom_of_stack + Stack_Size
SAR EQU 0x42000000 ; Start Alias Region
RCC EQU 0x40021000
; registers addresses
RCC_CR EQU RCC+0x0
RCC_CFGR EQU RCC+0x4
; bits numbers
HSEON EQU 16
HSION EQU 0
HSERDY EQU 17
HSIRDY EQU 1
PLLSRC EQU 16
PLLMUL EQU 18
PLLON EQU 24
PLLRDY EQU 25
SW EQU 1
	
Freq EQU 48000/5 -1;48000 - ��� � K��
Time equ 1235

	AREA RESET, DATA, READONLY
	DCD top_of_stack ;Top of Stack
	DCD Start
	AREA MY_CODE, CODE, READONLY
	ENTRY
Start
InitClock
	mov r9, #1
	ldr r0, =SAR+(RCC_CR&0x00FFFFFF)*0x20+HSEON*4;��������� HSE ���������
	str r9,[r0]
	ldr r0, =RCC_CR;��� Clock control register 
wait_hserdy
	ldr r10,[r0]
	tst r10,#(1<<HSEON);���� ��������� �������
	beq wait_hserdy
	ldr r0,=RCC_CFGR;��� Clock configuration register 
	ldr r10,=(1<<PLLSRC) + (4<<PLLMUL);��� � PLLMUL 4, ������ ��� (4+2)=6 =>(6*8=48), � ���������� ������ �� ���������  HSE - � PLLSRC ����� 1
	str r10,[r0]
	ldr r0,=SAR+(RCC_CR&0x00FFFFFF)*0x20+PLLON*4;��������� ������� � ���� ��� ��������� ������ PLL
	str r9,[r0]
	ldr r0, =RCC_CR;��� Clock control register 
wait_pllrdy
	ldr r10,[r0]
	tst r10, #(1<<PLLRDY);� ���� ���������� PLL, ��������������� ���������.
	beq wait_pllrdy
	ldr r0,=SAR+(RCC_CFGR&0x00FFFFFF)*0x20+SW*4;� ������� ���� ����� ����� ������� �������� ��� ������������ SYSCLK.(HSE-1)
	str r9,[r0]
finish

	ldr r0,=Freq
	ldr r1,=Time
TimeLoop
millisLoop
	sub r0,#1
	CMP r0,#0
	bne millisLoop	
	ldr r0,=Freq
	sub r1,#1
	CMP r1,#0
	bne TimeLoop 
	nop
	END
