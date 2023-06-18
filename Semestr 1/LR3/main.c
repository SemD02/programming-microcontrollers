#include <stdlib.h>
typedef struct
{
	union
	{
		__UINT64_TYPE__ unique_serial_code;
		struct
		{
			__UINT8_TYPE__ CRC_serialCode;		
			__UINT8_TYPE__ serialNumber[6];
			__UINT8_TYPE__ familyCode;
		};
	};
	float logData[100];
	float finalTemperature;
	union
	{
		struct
		{
			union
			{
				__UINT16_TYPE__ temperature;
				struct
				{
				__UINT8_TYPE__ temperature_LSB ;
				__UINT8_TYPE__ temperature_MSB ;
				};
			};
			__UINT8_TYPE__ TH_register;
			__UINT8_TYPE__ TL_register;
			__UINT8_TYPE__ configuratioun_register;
			__UINT8_TYPE__ reserved_1;
			__UINT8_TYPE__ reserved_2;
			__UINT8_TYPE__ reserved_3;
			__UINT8_TYPE__ CRC_scratchpad;
		};
		__UINT8_TYPE__ scratchpad[9];
	};
}DS18B20_;

void ini_DS18B20(__UINT64_TYPE__ unique_serial_code);
#define DS18B20 ((DS18B20_ *) (__UINT32_TYPE__)0x20001000)
#define SEARCH_ROM 0xF0
#define READ_ROM 0x33
#define MATCH_ROM 0x55
#define SCIP_ROM 0xCC
#define ALARM_SEARCH 0xEC
#define CONVERT_T 0x44
#define WRITE_SCRATCHPAD 0x4E
#define READ_SCRATCHPAD 0xBE
#define COPY_SCRATCHPAD 0x48
#define RECALL_E 0xB8
#define READ_POWER_SUPPLY 0xB4
void ini_DS18B20(__UINT64_TYPE__ unique_serial_code)
{
	DS18B20->unique_serial_code=unique_serial_code;
	DS18B20->finalTemperature=0.f;
	int i;
	for(i=0;i<9;i++)
		DS18B20->scratchpad[i]=0;
	for(i=0;i<100;i++)
		DS18B20->logData[i]=23;
	//read scratchpad ----> initial setting
}
int main()
{
	ini_DS18B20(155);
	DS18B20->scratchpad[1]=10;
	__UINT8_TYPE__ i =DS18B20->temperature_MSB;
}
