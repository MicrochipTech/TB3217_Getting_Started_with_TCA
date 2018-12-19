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
#define PERIOD_EXAMPLE_VALUE    (0x0CB6)

#include <avr/io.h>
#include <avr/interrupt.h>
/*Using default clock 3.33MHz */

void TCA0_init(void);
void PORT_init(void);

void TCA0_init(void)
{
    /* enable overflow interrupt */
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
    
    /* set Normal mode */
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
    
    /* disable event counting */
    TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);
    
    /* set the period */
    TCA0.SINGLE.PER = PERIOD_EXAMPLE_VALUE;  
    
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc         /* set clock source (sys_clk/256) */
                      | TCA_SINGLE_ENABLE_bm;                /* start timer */
}

void PORT_init(void)
{
    /* set pin 0 of PORT A as output */
    PORTA.DIR |= PIN0_bm;
}

ISR(TCA0_OVF_vect)
{
    /* Toggle PIN 0 of PORT A */
    PORTA.OUTTGL = PIN0_bm;
    
    /* The interrupt flag has to be cleared manually */
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main(void)
{
    PORT_init();
    
    TCA0_init();
    
    /* enable global interrupts */
    sei();
    
    while (1) 
    {
        ;
    }
}
