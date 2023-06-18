#ifndef BIT_OP1
#define BIT_OP1
#define bitFill(input, mask) input|mask
#define bitErase(input, mask) input&mask
#define bitInverse(input, mask) input^mask
#define linearShift(type,input, numShifts,side) side?input>>numShifts:(type)(input<<numShifts)
#define cycleShift(type,input, numShifts,side) (type)(side?(type)(input>>numShifts)|(type)(input<<(sizeof(type)*8-numShifts)):(type)(input<<numShifts)|(type)(input>>(sizeof(type)*8-numShifts)))
#endif
