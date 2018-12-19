/**
* \file main.c
*
* \brief Main source file.
*
(c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*
*/
#define PERIOD_EXAMPLE_VALUE_L        (0xCF)
#define PERIOD_EXAMPLE_VALUE_H        (0x44)
#define DUTY_CYCLE_EXAMPLE_VALUE_L    (0x68)
#define DUTY_CYCLE_EXAMPLE_VALUE_H    (0x11)

#include <avr/io.h>
/*Using default clock 3.33MHz */

void TCA0_init(void);
void PIN_init(void);
void TCA0_hardReset(void);

void TCA0_init(void)
{
    /* set waveform output on PORT A */
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTA_gc;
    
    /* enable split mode */
    TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;                 
    
    TCA0.SPLIT.CTRLB = TCA_SPLIT_HCMP0EN_bm        /* enable compare channel 0 for the higher byte */
                     | TCA_SPLIT_LCMP0EN_bm;    /* enable compare channel 0 for the lower byte */
    
    /* set the PWM frequencies and duty cycles */
    TCA0.SPLIT.LPER = PERIOD_EXAMPLE_VALUE_L;                          
    TCA0.SPLIT.LCMP0 = DUTY_CYCLE_EXAMPLE_VALUE_L;                           
    TCA0.SPLIT.HPER = PERIOD_EXAMPLE_VALUE_H;                             
    TCA0.SPLIT.HCMP0 = DUTY_CYCLE_EXAMPLE_VALUE_H;                               
    
    TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV16_gc    /* set clock source (sys_clk/16) */
                     | TCA_SPLIT_ENABLE_bm;         /* start timer */
}

void PIN_init(void)
{
    PORTA.DIR |= PIN0_bm    /* set pin 0 of PORT A as output */
              | PIN3_bm;    /* set pin 3 of PORT A as output */
}

/* must be used when switching from single mode to split mode */
void TCA0_hardReset(void)
{
    /* stop timer */
    TCA0.SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);  
    
    /* force a hard reset */
    TCA0.SINGLE.CTRLESET = TCA_SINGLE_CMD_RESET_gc; 
}

int main(void)
{
    PIN_init();
    
    TCA0_init();
    
    while (1) 
    {
        ;
    }
}
