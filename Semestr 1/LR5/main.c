#include <stdlib.h>
__UINT32_TYPE__ CRC_bit_alg32(__UINT32_TYPE__ Poly,__UINT32_TYPE__ Init,__UINT8_TYPE__ * data,__UINT64_TYPE__ dataSize,__UINT8_TYPE__ XorOut,__UINT8_TYPE__ resRefl) ;
__UINT32_TYPE__ * CRC_getTable(__UINT32_TYPE__ Poly);
__UINT32_TYPE__ getCRCuseTable(__UINT32_TYPE__ * table,__UINT32_TYPE__ Init,__UINT8_TYPE__ * data,__UINT64_TYPE__ dataSize,__UINT8_TYPE__ XorOut,__UINT8_TYPE__ resRefl);

__UINT32_TYPE__ CRC_bit_alg32(__UINT32_TYPE__ Poly,__UINT32_TYPE__ Init,__UINT8_TYPE__ * data,__UINT64_TYPE__ dataSize,__UINT8_TYPE__ XorOut, __UINT8_TYPE__ resRefl) 
{
	__UINT64_TYPE__ i;
	__UINT8_TYPE__ j;
	__UINT32_TYPE__ crc=Init;
	for(i=0;i<dataSize;i++)
	{
		__UINT32_TYPE__ shiftByte=(((__UINT32_TYPE__) data[i])<<24);
		crc^=shiftByte;
		for(j=0;j<8;j++)
		{
			__UINT32_TYPE__ lastBit = crc&0x80000000;
			crc<<=1;
			if(lastBit)
			{
				crc^=Poly;
			}
		}
	}
	if(resRefl)
	{//asm--BSWAP 
		__UINT32_TYPE__ crc1=0;
		for(i=0;i<32;i++)
		{
			if((crc>>i)&1)
				crc1|=1<<(31-i);
		}
		crc=crc1;
	}
	return XorOut?~crc:crc;	
}

__UINT32_TYPE__ * CRC_getTable(__UINT32_TYPE__ Poly)
{
	__UINT32_TYPE__ * crcTable=calloc(256,sizeof(__UINT32_TYPE__));
	__UINT32_TYPE__ i,j;
	for(i=0;i<256;i++)
	{
		crcTable[i]=i<<24;
		for(j=0;j<8;j++)
		{
			__UINT32_TYPE__ lastBit = crcTable[i]>>31;
			crcTable[i]<<=1;
			if(lastBit>0)
			{
				crcTable[i]^=Poly;
			}
		}
	}
	return 	crcTable;
}

__UINT32_TYPE__ getCRCuseTable(__UINT32_TYPE__ * table,__UINT32_TYPE__ Init,__UINT8_TYPE__ * data,__UINT64_TYPE__ dataSize,__UINT8_TYPE__ XorOut,__UINT8_TYPE__ resRefl)
{
	__UINT64_TYPE__ i;
	__UINT32_TYPE__ crc=Init;

	for(i=0;i<dataSize;i++)
	{
		__UINT32_TYPE__ R=((crc>>24) ^ data[i]) & 0xFF ;
		crc=crc<<8;
		crc^=table[R];
	}
	if(resRefl)
	{
		__UINT32_TYPE__ crc1=0;
		for(i=0;i<32;i++)
		{
			if((crc>>i)&1)
				crc1|=1<<(31-i);
		}
		crc=crc1;
	}
	return XorOut?~crc:crc;	
}

int main()
{
	__UINT8_TYPE__ data[10]={'1','2','3','4','5','6','7','8','9'};
	__UINT32_TYPE__ C=CRC_bit_alg32(0x04C11DB7,0xFFFFFFFF,data,5,1,1);
 	__UINT32_TYPE__ * CRCTable=CRC_getTable(0x04C11DB7);
	__UINT32_TYPE__ C1 = getCRCuseTable(CRCTable,0xFFFFFFFF,data,5,1,1);
	return 0;
}
