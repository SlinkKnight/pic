#include <16F877A.h>
#device adc=10
#use delay(crystal=4MHz)
#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT

#define LCD_RS_PIN      PIN_D7
#define LCD_RW_PIN      PIN_D6
#define LCD_ENABLE_PIN  PIN_D5
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D3
#define LCD_DATA6       PIN_D2
#define LCD_DATA7       PIN_D1

#include <lcd.c>

int8 PR2;

void main() {
    setup_adc_ports(ALL_ANALOG);
    setup_adc(ADC_CLOCK_INTERNAL);

    lcd_init();

    setup_timer_2(T2_DIV_BY_16, 124, 1);
    setup_ccp1(CCP_PWM);

    while (1) {
        set_adc_channel(0); delay_us(20);
        
        PR2 = (int8)(read_adc() / 4.0);
        setup_timer_2(T2_DIV_BY_16, PR2, 1);

        set_adc_channel(1); delay_us(20);
        set_pwm1_duty((int16)((float)((PR2 + 1) * 4 * (read_adc() / 1023.0))));

        printf(lcd_putc, "\fDt:%2.0f%%", (read_adc() / 1023.0) * 100);
        printf(lcd_putc, "\nFreq: %5.1f Hz", 62500.0 / (PR2 + 1));

        delay_ms(200);
    }
}