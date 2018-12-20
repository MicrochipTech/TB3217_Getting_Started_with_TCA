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
#define PERIOD_EXAMPLE_VALUE        (0x01A0)
#define DUTY_CYCLE_EXAMPLE_VALUE    (0x00D0)

#include <avr/io.h>
/*Using default clock 3.33MHz */

void TCA0_init(void);
void PORT_init(void);

void TCA0_init(void)
{
    /* set waveform output on PORT A */
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTA_gc;
    
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm            /* enable compare channel 0 */
                      | TCA_SINGLE_WGMODE_DSBOTTOM_gc;    /* set dual-slope PWM mode */
    
    /* disable event counting */
    TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm); 
    
    /* set PWM frequency and duty cycle (50%) */
    TCA0.SINGLE.PERBUF  = PERIOD_EXAMPLE_VALUE;       
    TCA0.SINGLE.CMP0BUF = DUTY_CYCLE_EXAMPLE_VALUE;  
    
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc        /* set clock source (sys_clk/4) */
                      | TCA_SINGLE_ENABLE_bm;           /* start timer */
}

void PORT_init(void)
{    
    /* set pin 0 of PORT A as output */    
    PORTA.DIR |= PIN0_bm;
}

int main(void)
{
    PORT_init();
    
    TCA0_init();
    
    /* Replace with your application code */
    while (1)
    {
        ;
    }
}
