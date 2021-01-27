/**
 * \file Lib.7SegLed.h
 * \author vEmagic (admin@vemagic.com)
 * \brief 
 * \version 0.0.1
 * \date 2020-11-02
 * 
 * @copyright Copyright (c) 2020, Sichuan Deyang DeYi Electronic Instrument Co., Ltd.
 * 
 */

#ifndef LIB_7SEG_LED_H
#define LIB_7SEG_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* TODO: 数码管能显示的字符数量 */
#define CHARACTER_NUMBER 17
/* 小数点在数码管字符集中的索引 */
#define DECIMAL_POINT_INDEX (CHARACTER_NUMBER - 1)

typedef struct _Drv7SegLed_ {
    uint8_t ui8DrvDigits; /*< The number of the 7-segment LED */
    void* pvDriver; /*< Pointer to a driver of the 7-segment LED */
} tDrv7SegLed;
/*-----------------------------------------------------------------------------------------------*/

/*************************************************************************************************
****************************** Interface Functions ***********************************************
**************************************************************************************************/

/**
 * \fn void DrvSevenSegLedClose(tDrv7SegLed* psDrv7SegLed, uint8_t ui8LedIndex)
 * \brief Open or enable a 7-segment LED dispaly
 * 
 * \param pvDriver Pointer to a 7-segment LED driver instance
 * \param ui8DriverIdx Specify the index of the 7-segment LED to be open
 * 
 * \note Please implement the interface function by yourself
 * \note 请自行实现此函数接口
 */
void DrvSevenSegLedOpen(void *pvDriver, uint8_t ui8DriverIdx);
/*-----------------------------------------------------------------------------------------------*/

/**
 * \fn void DrvSevenSegLedClose(tDrv7SegLed* psDrv7SegLed, uint8_t ui8LedIndex)
 * \brief Close a 7-segment LED display
 * 
 * \param pvDriver Pointer to a 7-segment LED driver instance
 * \param ui8LedIndex Specify the index of the 7-segment LED to be closed
 * 
 * \note Please implement the interface function by yourself
 * \note 请自行实现此函数接口
 */
void DrvSevenSegLedClose(void *pvDriver, uint8_t ui8LedIndex);
/*-----------------------------------------------------------------------------------------------*/

/**
 * \fn void DrvOneSevenSegLedUpdate(void* pvDriver, uint8_t ui8LedIndex, 
 *         uint8_t ui8Number, bool bShowDecimalPoint)
 * \brief Update the diaplay a 7-segment LED
 * 
 * \param pvDriver Pointer to a 7-segment LED driver instance
 * \param ui87SegLedIndex Specify the index of the 7-segment LEDs to be update dispaly
 * \param ui8Number The update value
 * \param bShowDecimalPoint true: display decimal pointer; false: Do not dispaly
 * 
 * \note Please implement the interface function by yourself
 * \note 请自行实现此函数接口
 */
void DrvOneSevenSegLedUpdate(void* pvDriver, uint8_t ui87SegLedIndex,
    uint8_t ui8Number, bool bShowDecimalPoint);
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/

/*************************************************************************************************
****************************** Module Functions ***********************************************
**************************************************************************************************/

/**
 * \fn void SevenSegLedCloseAll(tDrv7SegLed* psDrv7SegLed)
 * \brief Close all 7-segment LED display
 * 
 * \param psDrv7SegLed Pointer to a \ref tDrv7SegLed instance
 */
void SevenSegLedCloseAll(tDrv7SegLed* psDrv7SegLed);

/**
 * \fn uint8_t SevenSegLedUpdate(tDrv7SegLed* psDrv7SegLed, uint8_t* pui8Value, 
 *         uint8_t ui8Size, uint32_t ui32DigitPoint)
 * \brief Update the 7-segment LEDs dispaly base on the array data
 * 
 * \param psDrv7SegLed Pointer to a \ref tDrv7SegLed instance
 * \param pui8Value Array data
 * \param ui8Size The number of array data
 * \param ui32DecimalPoint The variable controls the decimal point
 *      display for all 7-segment LED by bit or logical, one-bit controls
 *      a 7-segment LED's decimal point display, the LSB controls the 
 *      7-segment digital tube of index bit 0. Up to 32 7-segment LEDs are supported
 * \return uint8_t The index number of next 7-segment LED
 */
uint8_t SevenSegLedUpdate(tDrv7SegLed* psDrv7SegLed, uint8_t* pui8Value, 
    uint8_t ui8Size, uint32_t ui32DecimalPoint);
/*-----------------------------------------------------------------------------------------------*/    

/**
 * \fn uint8_t SevenSegLedUpdateString(tDrv7SegLed* psDrv7SegLed, char* pcString)
 * \brief Update the 7-segment LEDs display base on the string
 * 
 * \param psDrv7SegLed Pointer to a \ref tDrv7SegLed instance
 * \param ui87SegLedIndex The display starts with the indexed 7-segment LED
 * \param pcString The string to display
 * \return uint8_t The index number of next 7-segment LED
 */
uint8_t SevenSegLedUpdateString(tDrv7SegLed* psDrv7SegLed, uint8_t ui87SegLedIndex, char* pcString);
/*-----------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LIB_7SEG_LED_H

/*************************************************************************************************
************* Copyright 2020 (C), Sichuan Deyang DeYi Electronic Instrument Co., Ltd *************
*************************************************************************************************/
