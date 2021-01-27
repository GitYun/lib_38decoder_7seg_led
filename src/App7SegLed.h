/**
 * \file App7SegLed.h
 * \author vEmagic (admin@vemgic.com)
 * \brief 
 * \version 0.1.0
 * \date 2020-11-03
 * 
 * Copyright 2020 (C), Sichuan Deyang DeYi Electronic Instrument Co., Ltd.
 * 
 */

#ifndef APP_7_SEG_LED_H
#define APP_7_SEG_LED_H

#ifdef __cplusplus
extern "C" {
#endif

tDrv7SegLed* App7SegLedInit(void);
void DisplayTask(uint16_t ui16Temperature, uint16_t ui16Humidity);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // APP_7_SEG_LED_H