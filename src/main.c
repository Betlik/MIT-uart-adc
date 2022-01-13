#include "stm8s.h"
#include "milis.h"
#include "swi2c.h"

/*#include "delay.h"*/
#include <stdio.h>
#include "../lib/uart.c"

#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define LED_HIGH   GPIO_WriteHigh(LED_PORT, LED_PIN)
#define LED_LOW  GPIO_WriteLow(LED_PORT, LED_PIN)
#define LED_TOGG GPIO_WriteReverse(LED_PORT, LED_PIN)

#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET) 


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    init_milis();
    swi2c_init();
}


int main(void)
{
    uint32_t time = 0;
    uint32_t cum = 69;
    uint8_t present;
    uint8_t error;
    uint8_t precteno[4];

    setup();
    init_uart();

    while (1) {

        present = swi2c_test_slave(0x68<<1);
        error = swi2c_read_buf(0x68<<1,0x0e,precteno,1);

        printf(precteno);
        printf(cum);
        if (milis() - time > 333 && BTN_PUSH) {
            LED_TOGG; 
            time = milis();

            printf("ssss𓆏\r\n");


        }

        /*LED_FLIP; */
        /*_delay_ms(333);*/
        /*printf("Funguje to!!!\n");*/
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
