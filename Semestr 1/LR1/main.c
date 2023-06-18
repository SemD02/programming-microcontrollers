#include "bit_op1.h"

int main()
{
	__UINT8_TYPE__ b=10,a=10,c=1;
	c=cycleShift(__UINT8_TYPE__,b,10,1);
	a=bitFill(b,0b1000000);
	a=bitErase(a,0b10111111);
	a=bitInverse(a,0b01000000);
	return 0;
}
