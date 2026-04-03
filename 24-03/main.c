#include <16F877A.h>

#device adc=10
#use delay(crystal=4MHz)

#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT

#include <lcd.c> 

#define LCD_RS_PIN      PIN_D7
#define LCD_RW_PIN      PIN_D6
#define LCD_ENABLE_PIN  PIN_D5
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D3
#define LCD_DATA6       PIN_D2
#define LCD_DATA7       PIN_D1


#define LEDA    PIN_C0
#define LEDB    PIN_C1
#define LEDC    PIN_C2
#define LEDD    PIN_C3
#define LEDE    PIN_C4
#define LEDF    PIN_C5
#define LEDG    PIN_C6

void clearDisplay(){
    output_high(LEDA);
    output_high(LEDB);
    output_high(LEDC);
    output_high(LEDD);
    output_high(LEDE);
    output_high(LEDF);
    output_high(LEDG);
}

void display1() {
    output_low(LEDB);
    output_low(LEDC);
}
void display2() {
    output_low(LEDD);
    output_low(LEDE);
    output_low(LEDG);
    output_low(LEDB);
    output_low(LEDA);
}
void display3() {
    output_low(LEDA);
    output_low(LEDB);
    output_low(LEDG);
    output_low(LEDC);
    output_low(LEDD);
}
void display4() {
    output_low(LEDC);
    output_low(LEDG);
    output_low(LEDF);
    output_low(LEDB);
}
void display5() {
    output_low(LEDA);
    output_low(LEDF);
    output_low(LEDG);
    output_low(LEDC);
    output_low(LEDD);
}
void display6() {
    output_low(LEDA);
    output_low(LEDF);
    output_low(LEDG);
    output_low(LEDC);
    output_low(LEDD);
    output_low(LEDE);

}
void display7() {
    output_low(LEDA);
    output_low(LEDB);
    output_low(LEDC);
}
void display8() {
    output_low(LEDA);
    output_low(LEDF);
    output_low(LEDG);
    output_low(LEDC);
    output_low(LEDD);
    output_low(LEDE);
    output_low(LEDB);
}
void display9() {
    output_low(LEDA);
    output_low(LEDF);
    output_low(LEDG);
    output_low(LEDC);
    output_low(LEDD);
    output_low(LEDB);
}
void display0() {
    output_low(LEDF);
    output_low(LEDE);
    output_low(LEDD);
    output_low(LEDC);
    output_low(LEDB);
    output_low(LEDA);
}

void main ()
{
    lcd_init(); 
    output_low(PIN_D0);

    while(1)
    {
        clearDisplay();
        display0();
        delay_ms(500);
        clearDisplay();
        display1();
        delay_ms(500);
        clearDisplay();
        display2();
        delay_ms(500);
        clearDisplay();
        display3();
        delay_ms(500);
        clearDisplay();
        display4();
        delay_ms(500);
        clearDisplay();
        display5();
        delay_ms(500);
        clearDisplay();
        display6();
        delay_ms(500);
        clearDisplay();
        display7();
        delay_ms(500);
        clearDisplay();
        display8();
        delay_ms(500);
        clearDisplay();
        display9();
        delay_ms(500);
    }
}