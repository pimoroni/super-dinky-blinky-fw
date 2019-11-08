#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#include "led_patterns.h"

#define LED1(x)         PWM0L=x 
#define LED2(x)         PWM1L=x


#define SWITCH_LONG_PRESS 1000


uint8_t led_pattern_no = 0;

uint8_t led_counter = 0;
uint8_t led_step = 1;
char  led_direction = 1;


void ExternalInterrupt0_ISR (void) __interrupt(3)
{
    // Do nothing, we just wake up from sleep.
    // PIF = 0x00; 
    clr_IE0;
}

void init_PWM(void) {
    P12_Quasi_Mode; PWM0_P12_OUTPUT_ENABLE; // LED1
    P11_Quasi_Mode; PWM1_P11_OUTPUT_ENABLE; // LED2
    set_PWMRUN;    
}

void disable_PWM(void) {
    P12_Quasi_Mode; PWM0_P12_OUTPUT_DISABLE; P12 = 0;
    P11_Quasi_Mode; PWM1_P11_OUTPUT_DISABLE; P11 = 0;
    clr_PWMRUN;
}


void main (void) 
{
    uint16_t switch_counter = 0;

    uint8_t *led_pattern_a = led_patterns[0];
    uint8_t *led_pattern_b = led_patterns[1];


    // //***** LIRC enable*****
    set_OSC1;
    clr_OSC0;  
    while((CKEN&SET_BIT0)==1);              //step4: check system clock switching OK or NG  
    clr_HIRCEN;

    Set_All_GPIO_Quasi_Mode;

    // Interrupt stuff:
    Enable_INT_Port3; // Connects P30 to Pin interrupt 0

    set_EX0;  // Enable external interrupt 0
    set_EA;   // Global enable interrupts
    set_IT0;

    // General PWM init
    PWM_INDEPENDENT_MODE;
    //PWM_CLOCK_DIV_2; // No divisor if commented
    PWMPH = 0x00; // 6 bit PWM range from 0 to 63
    PWMPL = 0x3F;
    init_PWM();

    P30_Quasi_Mode;
    P30 = 1;

	while(1) {

        if (!P30) {
            switch_counter = 0;

            while (!P30) {
                switch_counter++;
                if (switch_counter == SWITCH_LONG_PRESS) {
                    break;
                }
            }

            if (switch_counter == SWITCH_LONG_PRESS) {
                disable_PWM();
                while (!P30) {}
                PIF = 0x00; 
                set_PD; // Enter power-down mode

                // Returning from power-down mode
                init_PWM();
                while (!P30) {}
            } else {
                    led_pattern_no++;
                    led_counter = 0;
                    if (led_pattern_no == PATTERN_AMOUNT) {
                        led_pattern_no = 0;
                    }
                    led_pattern_a = led_patterns[led_pattern_no*2];
                    led_pattern_b = led_patterns[led_pattern_no*2+1];

            }

            while (!P30) {}
        }

        led_counter++;
        LED1(led_pattern_a[led_counter]);

        if (PWM0L > 64) { // We've reached the end of the pattern, jump back to beginning
            led_counter = 0;
            LED1(led_pattern_a[led_counter]);
        }

        LED2(led_pattern_b[led_counter]);
        set_LOAD;

	}

}

