#include <16F877A.h>
#device adc=8
#use delay(crystal=4MHz)

#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT

#define LCD_RS_PIN PIN_D7
#define LCD_RW_PIN PIN_D6
#define LCD_ENABLE_PIN PIN_D5
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D3
#define LCD_DATA6 PIN_D2
#define LCD_DATA7 PIN_D1

#include <lcd.c>
long int contador = 0;
int horas = 0, minutos = 0, segundos = 0;

#INT_TIMER0

int8 segUnd  = 0;
int8 segDez  = 0;
int8 minUnd  = 0;
int8 minDez  = 0;
int8 horaUnd = 0;
int8 horaDez = 0;

void interrupt_t0() {
    clear_interrupt(INT_TIMER0);
    set_timer0(6);
    if(contador == 1000) {
        segUnd++;
        if(segUnd == 10) {
            segUnd = 0;
            segDez++;
            if(segDez == 6) {
                segDez = 0;
                minUnd++;
                if(minUnd == 10) {
                    minUnd = 0;
                    minDez++;
                    if(minDez == 6) {
                        minDez = 0;
                        horaUnd++;
                        if(horaUnd == 10) {
                            horaUnd = 0;
                            horaDez++;
                        }
                        if(horaDez == 2 && horaUnd == 4) {
                            horaUnd = 0;
                            horaDez = 0;
                        }
                    }
                }
            }
        }
    }
}

void main() {
    enable_interrupts(GLOBAL);
    enable_interrupts(INT_TIMER0);
    setup_timer_0(T0_INTERNAL || T0_DIV_4);
    set_timer0(6);
    lcd_init();

    while(TRUE) {
        printf(lcd_putc, "\fRelogio %d:%d:%d", horas, minutos, segundos);
        delay_ms(1000);
    }
}