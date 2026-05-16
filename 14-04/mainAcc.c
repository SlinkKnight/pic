#include <16F877A.h>

#device adc=10
#use delay(crystal=4MHz)
#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT

#define LEDA     PIN_D4
#define ACT1     PIN_C7
#define ACT2     PIN_C6    
#define ACT3     PIN_C5
#define ACT4     PIN_C4
#define ACT5     PIN_D2
#define ACT6     PIN_D3
#define TEST_PIN PIN_D0

int8 segs[10] = {
    0b10000100, // 0
    0b10111110, // 1
    0b11001000, // 2
    0b10011000, // 3
    0b10110010, // 4
    0b10010001, // 5
    0b10000001, // 6
    0b10111100, // 7
    0b10000000, // 8
    0b10010000  // 9
};

void choose(int8 num) {
    output_b(segs[num]);
}

int8 segUnd = 0;
int8 segDez = 0;
int8 minUnd = 0;
int8 minDez = 0;
int8 horaUnd = 0;
int8 horaDez = 0;

void displayRefresh() {
    output_high(ACT1);
    output_high(ACT2);
    output_high(ACT3); 
    output_high(ACT4);
    output_high(ACT5); 
    output_high(ACT6);

    output_low(ACT1); 
    choose(horaDez);
    delay_us(500);
    output_high(ACT1);

    output_low(ACT2); 
    choose(horaUnd);
    delay_us(500);
    output_high(ACT2);

    output_low(ACT3); 
    choose(minDez);
    delay_us(500);
    output_high(ACT3);

    output_low(ACT4); 
    choose(minUnd);
    delay_us(500);
    output_high(ACT4);

    output_low(ACT5); 
    choose(segDez);
    delay_us(500);
    output_high(ACT5);

    output_low(ACT6); 
    choose(segUnd);
    delay_us(500);
    output_high(ACT6);
    delay_us(3);
}

void testes() {
    int16 i;

    for(i = 0; i < 500; i++) {
        output_low(ACT1); 
        choose(8); 
        delay_ms(1); 
        output_high(ACT1);

        output_low(ACT2); 
        choose(8); 
        delay_ms(1); 
        output_high(ACT2);

        output_low(ACT3); 
        choose(8); 
        delay_ms(1); 
        output_high(ACT3);

        output_low(ACT4); 
        choose(8); 
        delay_ms(1); 
        output_high(ACT4);

        output_low(ACT5); 
        choose(8); 
        delay_ms(1); 
        output_high(ACT5);

        output_low(ACT6); 
        choose(8); 
        delay_ms(1); 
        output_high(ACT6);
    }
}

void increment() {
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

void main() {
    int iter = 0;

    testes();

    while(1) {
        output_low(TEST_PIN);
        displayRefresh();
        output_high(TEST_PIN);

        iter++;
        if(iter >= 310) {
            iter = 0;
            increment();
        }
    }
}