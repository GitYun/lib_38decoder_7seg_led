/**
 * \file Drv7SegLed.c
 * \author vEmagic (admin@vemagic.com)
 * \brief 
 * \version 0.0.1
 * \date 2020-11-01
 * 
 * @copyright Copyright (c) 2020, Sichuan Deyang DeYi Electronic Instrument Co., Ltd.
 * 
 */

#include "main.h"
#include "Drv38Decoder.h"
#include "Lib.7SegLed.h"

/* TODO: 延时1ms刷新数码管 */
/* 由于此驱动对应的硬件需要逐段点亮数码管的LED, 故在点亮一段数码管的LED后延时100us,
 * 利用余辉效应，看起来就如一个数码管的每段被同时点亮了; 一个数码管最多延时8x0.1ms=0.8ms */
#define DRV_ONE_7SEG_LED_DELAY_1MS() SysTick_uDelay(100)

/*< TODO: 38译码器到数码管映射的数量 */
#define NUMBER_38DECODER_TO_7SEG_LED_MAP 6

/*< TODO: 38译码器的A2A1A0输入到驱动数码管的输出编码 */
#define SSL_a 0x03
#define SSL_b 0x01
#define SSL_c 0x02
#define SSL_d 0x05
#define SSL_e 0x07
#define SSL_f 0x04
#define SSL_g 0x06
#define SSL_dp 0x0
#define SSL_off 0xFF

static const uint8_t pui8SSL_0[] = {SSL_a, SSL_b, SSL_c, SSL_d, SSL_e, SSL_f, SSL_dp};
static const uint8_t pui8SSL_1[] = {SSL_b, SSL_c, SSL_dp};
static const uint8_t pui8SSL_2[] = {SSL_a, SSL_b, SSL_d, SSL_e, SSL_g, SSL_dp};
static const uint8_t pui8SSL_3[] = {SSL_a, SSL_b, SSL_c, SSL_d, SSL_g, SSL_dp};
static const uint8_t pui8SSL_4[] = {SSL_b, SSL_c, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_5[] = {SSL_a, SSL_c, SSL_d, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_6[] = {SSL_a, SSL_c, SSL_d, SSL_e, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_7[] = {SSL_a, SSL_b, SSL_c, SSL_dp};
static const uint8_t pui8SSL_8[] = {SSL_a, SSL_b, SSL_c, SSL_d, SSL_e, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_9[] = {SSL_a, SSL_b, SSL_c, SSL_d, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_A[] = {SSL_a, SSL_b, SSL_c, SSL_e, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_b[] = {SSL_c, SSL_d, SSL_e, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_C[] = {SSL_a, SSL_d, SSL_e, SSL_f, SSL_dp};
static const uint8_t pui8SSL_d[] = {SSL_b, SSL_c, SSL_d, SSL_e, SSL_g, SSL_dp};
static const uint8_t pui8SSL_E[] = {SSL_a, SSL_d, SSL_e, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_F[] = {SSL_a, SSL_e, SSL_f, SSL_g, SSL_dp};
static const uint8_t pui8SSL_dp[]= {SSL_dp};

static const tInputEncode g_ps7SegLedFontEncode[CHARACTER_NUMBER] = {
    {0,  6, pui8SSL_0}, // 0
    {1,  2, pui8SSL_1}, // 1
    {2,  5, pui8SSL_2}, // 2
    {3,  5, pui8SSL_3}, // 3
    {4,  4, pui8SSL_4}, // 4
    {5,  5, pui8SSL_5}, // 5
    {6,  6, pui8SSL_6}, // 6
    {7,  3, pui8SSL_7}, // 7
    {8,  7, pui8SSL_8}, // 8
    {9,  6, pui8SSL_9}, // 9
    {10, 6, pui8SSL_A}, // A
    {11, 5, pui8SSL_b}, // b
    {12, 4, pui8SSL_C}, // C
    {13, 5, pui8SSL_d}, // d
    {14, 5, pui8SSL_E}, // E
    {15, 4, pui8SSL_F}, // F
    {16, 1, pui8SSL_dp}, // The 7-segment led display only a '.'
};

static t38Decoder g_ps38Decoder[NUMBER_38DECODER_TO_7SEG_LED_MAP];
/*-----------------------------------------------------------------------------------------------*/

static void Drv7SegLed(t38Decoder* ps38Decoder, uint8_t ui8LedField);

/* Initial the 38-decoder */
t38Decoder* Drv38DecoderInit(uint8_t ui8Size)
{
    uint8_t idx;
    for (idx = 0; idx < NUMBER_38DECODER_TO_7SEG_LED_MAP && idx < ui8Size; ++idx)
    {
        g_ps38Decoder[idx].psInputEncode = (tInputEncode *)g_ps7SegLedFontEncode;
        g_ps38Decoder[idx].pfnDecode = Drv7SegLed;
    }

    return g_ps38Decoder;
}
/*-----------------------------------------------------------------------------------------------*/

void DrvSevenSegLedOpen(void *pvDriver, uint8_t ui8DriverIdx)
{
    t38Decoder *ps38Decoder = &((t38Decoder *)pvDriver)[ui8DriverIdx];
    Drv38DecoderOpen(ps38Decoder);
}
/*-----------------------------------------------------------------------------------------------*/

void DrvSevenSegLedClose(void *pvDriver, uint8_t ui8DriverIdx)
{
    t38Decoder *ps38Decoder = &((t38Decoder *)pvDriver)[ui8DriverIdx];
    Drv38DecoderClose(ps38Decoder);
}
/*-----------------------------------------------------------------------------------------------*/

/* ui8Number range: 0 ~ (CHARACTER_NUMBER - 1) */
void DrvOneSevenSegLedUpdate(void* pvDriver, uint8_t ui87SegLedIndex,
    uint8_t ui8Number, bool bShowDecimalPoint)
{
    t38Decoder *ps38Decoder = &((t38Decoder *)pvDriver)[ui87SegLedIndex];
    tInputEncode *psEncode = &ps38Decoder->psInputEncode[ui8Number % CHARACTER_NUMBER];
    uint8_t size = psEncode->ui8Size;
    uint8_t idx;

    if (bShowDecimalPoint)
    {
    	size += 1; // Display the decimal point
    }

    for (idx = 0; idx < size; ++idx)
    {
        ps38Decoder->pfnDecode(ps38Decoder, psEncode->pui8Encode[idx]);
    }

    // Eliminates the strong display of the last light up LED segment
    DECODER_PIN_LOW(ps38Decoder->e3.sPort, ps38Decoder->e3.sPin);
}
/*-----------------------------------------------------------------------------------------------*/

static void Drv7SegLed(t38Decoder* ps38Decoder, uint8_t ui8LedField)
{
    bool bEnable38Decoder = true;

    // Eliminates Blanking
    DECODER_PIN_LOW(ps38Decoder->e3.sPort, ps38Decoder->e3.sPin);

    switch (ui8LedField)
    {
        case SSL_off:
            bEnable38Decoder = false;
            break;

        case SSL_dp:
            DECODER_PIN_LOW(ps38Decoder->a2.sPort, ps38Decoder->a2.sPin);
            DECODER_PIN_LOW(ps38Decoder->a1.sPort, ps38Decoder->a1.sPin);
            DECODER_PIN_LOW(ps38Decoder->a0.sPort, ps38Decoder->a0.sPin);
            break;

        case SSL_b:
            DECODER_PIN_LOW(ps38Decoder->a2.sPort, ps38Decoder->a2.sPin);
            DECODER_PIN_LOW(ps38Decoder->a1.sPort, ps38Decoder->a1.sPin);
            DECODER_PIN_HIGH(ps38Decoder->a0.sPort, ps38Decoder->a0.sPin);
            break;

        case SSL_c:
            DECODER_PIN_LOW(ps38Decoder->a2.sPort, ps38Decoder->a2.sPin);
            DECODER_PIN_HIGH(ps38Decoder->a1.sPort, ps38Decoder->a1.sPin);
            DECODER_PIN_LOW(ps38Decoder->a0.sPort, ps38Decoder->a0.sPin);
            break;

        case SSL_a:
            DECODER_PIN_LOW(ps38Decoder->a2.sPort, ps38Decoder->a2.sPin);
            DECODER_PIN_HIGH(ps38Decoder->a1.sPort, ps38Decoder->a1.sPin);
            DECODER_PIN_HIGH(ps38Decoder->a0.sPort, ps38Decoder->a0.sPin);
            break;

        case SSL_f:
            DECODER_PIN_HIGH(ps38Decoder->a2.sPort, ps38Decoder->a2.sPin);
            DECODER_PIN_LOW(ps38Decoder->a1.sPort, ps38Decoder->a1.sPin);
            DECODER_PIN_LOW(ps38Decoder->a0.sPort, ps38Decoder->a0.sPin);
            break;

        case SSL_d:
            DECODER_PIN_HIGH(ps38Decoder->a2.sPort, ps38Decoder->a2.sPin);
            DECODER_PIN_LOW(ps38Decoder->a1.sPort, ps38Decoder->a1.sPin);
            DECODER_PIN_HIGH(ps38Decoder->a0.sPort, ps38Decoder->a0.sPin);
            break;

        case SSL_g:
            DECODER_PIN_HIGH(ps38Decoder->a2.sPort, ps38Decoder->a2.sPin);
            DECODER_PIN_HIGH(ps38Decoder->a1.sPort, ps38Decoder->a1.sPin);
            DECODER_PIN_LOW(ps38Decoder->a0.sPort, ps38Decoder->a0.sPin);
            break;

        case SSL_e:
            DECODER_PIN_HIGH(ps38Decoder->a2.sPort, ps38Decoder->a2.sPin);
            DECODER_PIN_HIGH(ps38Decoder->a1.sPort, ps38Decoder->a1.sPin);
            DECODER_PIN_HIGH(ps38Decoder->a0.sPort, ps38Decoder->a0.sPin);
            break;
        
        default:
            // Whether use the previous input value
            break;
    }

    if (bEnable38Decoder)
    {
        DECODER_PIN_HIGH(ps38Decoder->e3.sPort, ps38Decoder->e3.sPin);
        DRV_ONE_7SEG_LED_DELAY_1MS();
    }
}
/*-----------------------------------------------------------------------------------------------*/
