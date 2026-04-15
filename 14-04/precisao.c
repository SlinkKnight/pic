#include <16F877A.h>
#device adc=10
#use delay(crystal=4MHz)
#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT

// Definições dos segmentos (mantidas iguais ao original)
#define LEDA    PIN_B1
#define LEDB    PIN_B0
#define LEDC    PIN_B6
#define LEDD    PIN_B5
#define LEDE    PIN_B4
#define LEDF    PIN_B3
#define LEDG    PIN_B2
#define LEDPT   PIN_B7

#define ACT1    PIN_C7
#define ACT2    PIN_C6    
#define ACT3    PIN_C5
#define ACT4    PIN_C4
#define ACT5    PIN_D2
#define ACT6    PIN_D3

// Pino de teste para o osciloscópio
#define TEST_PIN  PIN_D0

void clearDisplay() {
    output_high(LEDA); output_high(LEDB); output_high(LEDC);
    output_high(LEDD); output_high(LEDE); output_high(LEDF);
    output_high(LEDG);
}

void display1() { output_low(LEDB); output_low(LEDC); }
void display2() { output_low(LEDD); output_low(LEDE); output_low(LEDG); output_low(LEDB); output_low(LEDA); }
void display3() { output_low(LEDA); output_low(LEDB); output_low(LEDG); output_low(LEDC); output_low(LEDD); }
void display4() { output_low(LEDC); output_low(LEDG); output_low(LEDF); output_low(LEDB); }
void display5() { output_low(LEDA); output_low(LEDF); output_low(LEDG); output_low(LEDC); output_low(LEDD); }
void display6() { output_low(LEDA); output_low(LEDF); output_low(LEDG); output_low(LEDC); output_low(LEDD); output_low(LEDE); }
void display7() { output_low(LEDA); output_low(LEDB); output_low(LEDC); }
void display8() { output_low(LEDA); output_low(LEDF); output_low(LEDG); output_low(LEDC); output_low(LEDD); output_low(LEDE); output_low(LEDB); }
void display9() { output_low(LEDA); output_low(LEDF); output_low(LEDG); output_low(LEDC); output_low(LEDD); output_low(LEDB); }
void display0() { output_low(LEDF); output_low(LEDE); output_low(LEDD); output_low(LEDC); output_low(LEDB); output_low(LEDA); }

void choose(int num) {
    clearDisplay();
    switch (num) {
        case 0: display0(); break;
        case 1: display1(); break;
        case 2: display2(); break;
        case 3: display3(); break;
        case 4: display4(); break;
        case 5: display5(); break;
        case 6: display6(); break;
        case 7: display7(); break;
        case 8: display8(); break;
        case 9: display9(); break;
        default: clearDisplay(); break;
    }
}

void displayRefresh(int h, int m, int s) {
    output_high(ACT1); output_high(ACT2); output_high(ACT3);
    output_high(ACT4); output_high(ACT5); output_high(ACT6);

    int horaDez = h / 10, horaUnd = h % 10;
    int minDez  = m / 10, minUnd  = m % 10;
    int segDez  = s / 10, segUnd  = s % 10;

    output_low(ACT1); choose(horaDez); delay_ms(5); output_high(ACT1);
    output_low(ACT2); choose(horaUnd); delay_ms(5); output_high(ACT2);
    output_low(ACT3); choose(minDez);  delay_ms(5); output_high(ACT3);
    output_low(ACT4); choose(minUnd);  delay_ms(5); output_high(ACT4);
    output_low(ACT5); choose(segDez);  delay_ms(5); output_high(ACT5);
    output_low(ACT6); choose(segUnd);  delay_ms(5); output_high(ACT6);
}

void main() {
    int i;
    output_low(TEST_PIN);
    
    while(TRUE) {
        output_high(TEST_PIN);
        for(i = 0; i < 100; i++) {   // 100 iterações
            displayRefresh(12, 34, 56);
        }
        output_low(TEST_PIN);
        delay_ms(1000);
    } 
}