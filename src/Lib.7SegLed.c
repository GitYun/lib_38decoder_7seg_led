/**
 * \file Lib.7SegLed.c
 * \author vEmagic (admin@vemagic.com)
 * \brief 
 * \version 0.0.1
 * \date 2020-11-02
 * 
 * @copyright Copyright (c) 2020, Sichuan Deyang DeYi Electronic Instrument Co., Ltd.
 * 
 */

#include "Lib.7SegLed.h"

void SevenSegLedCloseAll(tDrv7SegLed* psDrv7SegLed)
{
    uint8_t idx;
    for (idx = 0; idx < psDrv7SegLed->ui8DrvDigits; ++idx)
    	DrvSevenSegLedClose(psDrv7SegLed->pvDriver, idx);
}
/*-----------------------------------------------------------------------------------------------*/

uint8_t SevenSegLedUpdate(tDrv7SegLed* psDrv7SegLed, uint8_t* pui8Value, 
    uint8_t ui8Size, uint32_t ui32DecimalPoint)
{
    uint8_t idx;
    for (idx = 0; idx < psDrv7SegLed->ui8DrvDigits && idx < ui8Size; ++idx)
    {
        DrvOneSevenSegLedUpdate(psDrv7SegLed->pvDriver, idx, pui8Value[idx], ui32DecimalPoint & (1UL << idx));
    }

    return idx;
}
/*-----------------------------------------------------------------------------------------------*/

uint8_t SevenSegLedUpdateString(tDrv7SegLed* psDrv7SegLed, uint8_t ui87SegLedIndex, char* pcString)
{
    uint8_t ui8SkipCount = 0;
    uint8_t idx = 0;
    for (; (idx - ui8SkipCount) < (psDrv7SegLed->ui8DrvDigits - ui87SegLedIndex) && pcString[idx] != '\0'; ++idx)
    {
        bool bDigitPointShow = false;
        uint8_t ui8Value = pcString[idx];
        
        if ('0' <= ui8Value && ui8Value <= '9')
        {
            ui8Value = ui8Value - '0';
        }
        else if ('A' <= ui8Value && ui8Value <= 'F')
        {
            ui8Value = ui8Value - 'A' + 10;
        }
        else if ('a' <= ui8Value && ui8Value <= 'f')
        {
            ui8Value = ui8Value - 'a' + 10;
        }
        else if ('.' == ui8Value)
        {
            ui8Value = DECIMAL_POINT_INDEX;
        }
        else
        {
            ++ui8SkipCount;
            continue;
        }
        
        bDigitPointShow = pcString[idx] != '.' && pcString[idx + 1] == '.';

        DrvOneSevenSegLedUpdate(psDrv7SegLed->pvDriver, ui87SegLedIndex + idx - ui8SkipCount, ui8Value, bDigitPointShow);

        if (bDigitPointShow)
        {
        	++idx;
        	++ui8SkipCount;
        }
    }

    return ui87SegLedIndex + idx - ui8SkipCount;
}
/*-----------------------------------------------------------------------------------------------*/

/*************************************************************************************************
************* Copyright 2020 (C), Sichuan Deyang DeYi Electronic Instrument Co., Ltd *************
*************************************************************************************************/
