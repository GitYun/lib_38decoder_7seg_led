/**
 * \file Drv38Decoder.h
 * \author vEmagic (admin@vemagic.com)
 * \brief 
 * \version 0.0.1
 * \date 2020-11-01
 * 
 * @copyright Copyright (c) 2020, Sichuan Deyang DeYi Electronic Instrument Co., Ltd.
 * 
 */

#ifndef DRV38DECODER_H
#define DRV38DECODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "stm32f0xx.h"
#include "stm32f0xx_ll_gpio.h"
/*-----------------------------------------------------------------------------------------------*/

#define DECODER_PIN_HIGH(port, pin) LL_GPIO_SetOutputPin((port), (pin)) //WRITE_REG((port)->BSRR, (pin))
#define DECODER_PIN_LOW(port, pin) LL_GPIO_ResetOutputPin((port), (pin)) //WRITE_REG((port)->BRR, (pin))

typedef GPIO_TypeDef* t38DecoderPort;
typedef uint32_t t38DecoderPin;

typedef struct {
	t38DecoderPort sPort;
	t38DecoderPin sPin;
} t38DecoderGpio;

typedef struct {
    uint8_t ui8Index; /*< Data encode index */
    uint8_t ui8Size; /*< Data encode array size of the member 'pui8Encode' */
    const uint8_t* const pui8Encode; /*< Data encode array */
} tInputEncode;

/* IC 74HC138 */
typedef struct _38Decoder_ {
	t38DecoderGpio a0;
	t38DecoderGpio a1;
	t38DecoderGpio a2;
	t38DecoderGpio e1;
	t38DecoderGpio e2;
	t38DecoderGpio e3;

    uint8_t *pui8Rsvd; /*< Reserved */
    tInputEncode* psInputEncode;
    void (*pfnDecode)(struct _38Decoder_* ps38Decoder, uint8_t ui8Encode);
} t38Decoder;
/*-----------------------------------------------------------------------------------------------*/

#define DRV_38DECODER_E1_ENABLE(port, pin)
#define DRV_38DECODER_E1_DISABLE(port, pin)
#define DRV_38DECODER_E2_ENABLE(port, pin)
#define DRV_38DECODER_E2_DISABLE(port, pin)
#define DRV_38DECODER_E3_ENABLE(port, pin) DECODER_PIN_HIGH((port), (pin))
#define DRV_38DECODER_E3_DISABLE(port, pin) DECODER_PIN_LOW((port), (pin))
/*-----------------------------------------------------------------------------------------------*/

#if 0
/**
 * \fn void Drv38DecoderOpen(t38Decoder* ps38Decoder)
 * \brief Enable a 38-decoder
 * 
 * \param ps38Decoder Pointer to the \ref t38Decoder instance
 */
static inline void Drv38DecoderOpen(t38Decoder* ps38Decoder)
{
    DRV_38DECODER_E1_ENABLE(ps38Decoder->e1.sPort, ps38Decoder->e1.sPin);
    DRV_38DECODER_E2_ENABLE(ps38Decoder->e2.sPort, ps38Decoder->e2.sPin);
    DRV_38DECODER_E3_ENABLE(ps38Decoder->e3.sPort, ps38Decoder->e3.sPin);
}
/*-----------------------------------------------------------------------------------------------*/

/**
 * \fn void Drv38DecoderClose(t38Decoder* ps38Decoder)
 * \brief Disable a 38-decoder
 * 
 * \param ps38Decoder Pointer to the \ref t38Decoder instance
 */
static inline void Drv38DecoderClose(t38Decoder* ps38Decoder)
{
    DRV_38DECODER_E1_ENABLE(ps38Decoder->e1.sPort, ps38Decoder->e1.sPin);
    DRV_38DECODER_E2_ENABLE(ps38Decoder->e2.sPort, ps38Decoder->e2.sPin);
    DRV_38DECODER_E3_DISABLE(ps38Decoder->e3.sPort, ps38Decoder->e3.sPin);
}
/*-----------------------------------------------------------------------------------------------*/

#else
/**
 * \fn void Drv38DecoderOpen(t38Decoder* ps38Decoder)
 * \brief Enable a 38-decoder
 * 
 * \param ps38Decoder Pointer to the \ref t38Decoder instance
 */
#define Drv38DecoderOpen(ps38Decoder) \
do { \
    DRV_38DECODER_E1_ENABLE((ps38Decoder)->e1.sPort, (ps38Decoder)->e1.sPin); \
    DRV_38DECODER_E2_ENABLE((ps38Decoder)->e2.sPort, (ps38Decoder)->e2.sPin); \
    DRV_38DECODER_E3_ENABLE((ps38Decoder)->e3.sPort, (ps38Decoder)->e3.sPin); \
} while (0)

/**
 * \fn void Drv38DecoderClose(t38Decoder* ps38Decoder)
 * \brief Disable a 38-decoder
 * 
 * \param ps38Decoder Pointer to the \ref t38Decoder instance
 */
#define Drv38DecoderClose(ps38Decoder) \
do { \
    DRV_38DECODER_E1_ENABLE((ps38Decoder)->e1.sPort, (ps38Decoder)->e1.sPin); \
    DRV_38DECODER_E2_ENABLE((ps38Decoder)->e2.sPort, (ps38Decoder)->e2.sPin); \
    DRV_38DECODER_E3_DISABLE((ps38Decoder)->e3.sPort, (ps38Decoder)->e3.sPin);\
} while (0)
#endif

/**
 * \fn t38Decoder* Drv38DecoderInit(void)
 * \brief Initial a 
 * 
 * \return t38Decoder* 
 */
t38Decoder* Drv38DecoderInit(uint8_t ui8Size);
/*-----------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DRV38DECODER_H

/*************************************************************************************************
************* Copyright 2020 (C), Sichuan Deyang DeYi Electronic Instrument Co., Ltd *************
*************************************************************************************************/