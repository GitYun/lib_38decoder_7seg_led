/**
 * \file App7SegLed.c
 * \author vEmagic (admin@vemagic.com)
 * \brief 
 * \version 0.0.1
 * \date 2020-11-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "itoa.h"
#include "main.h"
#include "Drv38Decoder.h"
#include "Lib.7SegLed.h"

static tDrv7SegLed g_s7SegLed;

tDrv7SegLed* App7SegLedInit(void)
{
	t38Decoder* ps38Decoder = Drv38DecoderInit(6);

	// 根据显示顺序分配GPIO
	(ps38Decoder[0]).e3.sPort = EN1_GPIO_Port;
	(ps38Decoder[0]).e3.sPin = EN1_Pin;
	(ps38Decoder[0]).a0.sPort = A0_1_GPIO_Port;
	(ps38Decoder[0]).a0.sPin = A0_1_Pin;
	(ps38Decoder[0]).a1.sPort = A1_1_GPIO_Port;
	(ps38Decoder[0]).a1.sPin = A1_1_Pin;
	(ps38Decoder[0]).a2.sPort = A2_1_GPIO_Port;
	(ps38Decoder[0]).a2.sPin = A2_1_Pin;

	(ps38Decoder[1]).e3.sPort = EN2_GPIO_Port;
	(ps38Decoder[1]).e3.sPin = EN2_Pin;
	(ps38Decoder[1]).a0.sPort = A0_2_GPIO_Port;
	(ps38Decoder[1]).a0.sPin = A0_2_Pin;
	(ps38Decoder[1]).a1.sPort = A1_2_GPIO_Port;
	(ps38Decoder[1]).a1.sPin = A1_2_Pin;
	(ps38Decoder[1]).a2.sPort = A2_2_GPIO_Port;
	(ps38Decoder[1]).a2.sPin = A2_2_Pin;

	(ps38Decoder[2]).e3.sPort = EN3_GPIO_Port;
	(ps38Decoder[2]).e3.sPin = EN3_Pin;
	(ps38Decoder[2]).a0.sPort = A0_3_GPIO_Port;
	(ps38Decoder[2]).a0.sPin = A0_3_Pin;
	(ps38Decoder[2]).a1.sPort = A1_3_GPIO_Port;
	(ps38Decoder[2]).a1.sPin = A1_3_Pin;
	(ps38Decoder[2]).a2.sPort = A2_3_GPIO_Port;
	(ps38Decoder[2]).a2.sPin = A2_3_Pin;

	(ps38Decoder[3]).e3.sPort = EN4_GPIO_Port;
	(ps38Decoder[3]).e3.sPin = EN4_Pin;
	(ps38Decoder[3]).a0.sPort = A0_4_GPIO_Port;
	(ps38Decoder[3]).a0.sPin = A0_4_Pin;
	(ps38Decoder[3]).a1.sPort = A1_4_GPIO_Port;
	(ps38Decoder[3]).a1.sPin = A1_4_Pin;
	(ps38Decoder[3]).a2.sPort = A2_4_GPIO_Port;
	(ps38Decoder[3]).a2.sPin = A2_4_Pin;

	(ps38Decoder[4]).e3.sPort = EN5_GPIO_Port;
	(ps38Decoder[4]).e3.sPin = EN5_Pin;
	(ps38Decoder[4]).a0.sPort = A0_5_GPIO_Port;
	(ps38Decoder[4]).a0.sPin = A0_5_Pin;
	(ps38Decoder[4]).a1.sPort = A1_5_GPIO_Port;
	(ps38Decoder[4]).a1.sPin = A1_5_Pin;
	(ps38Decoder[4]).a2.sPort = A2_5_GPIO_Port;
	(ps38Decoder[4]).a2.sPin = A2_5_Pin;

	(ps38Decoder[5]).e3.sPort = EN6_GPIO_Port;
	(ps38Decoder[5]).e3.sPin = EN6_Pin;
	(ps38Decoder[5]).a0.sPort = A0_6_GPIO_Port;
	(ps38Decoder[5]).a0.sPin = A0_6_Pin;
	(ps38Decoder[5]).a1.sPort = A1_6_GPIO_Port;
	(ps38Decoder[5]).a1.sPin = A1_6_Pin;
	(ps38Decoder[5]).a2.sPort = A2_6_GPIO_Port;
	(ps38Decoder[5]).a2.sPin = A2_6_Pin;

    g_s7SegLed.ui8DrvDigits = 6;
    g_s7SegLed.pvDriver = ps38Decoder;

    SevenSegLedCloseAll(&g_s7SegLed);

    return &g_s7SegLed;
}
/*-----------------------------------------------------------------------------------------------*/

void DisplayTask(uint16_t ui16Temperature, uint16_t ui16Humidity)
{
#define ADD_DECIMAL_POINT(string, pos) \
do { \
	uint8_t ui8Tmp = string[pos]; \
	string[pos] = '.'; \
	string[pos + 1] = ui8Tmp; \
} while(0)

	char temperatureString[7] = {0};
	char humidityString[7] = {0};

	uitoa_r(ui16Temperature, temperatureString, 10);
	ADD_DECIMAL_POINT(temperatureString, 2);
	SevenSegLedUpdateString(&g_s7SegLed, 0, temperatureString);

	uitoa_r(ui16Humidity, humidityString, 10);
	ADD_DECIMAL_POINT(humidityString, 2);
	SevenSegLedUpdateString(&g_s7SegLed, 3, humidityString);
}
/*-----------------------------------------------------------------------------------------------*/
