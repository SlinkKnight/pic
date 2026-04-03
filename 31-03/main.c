#include <16F877A.h>

#device adc=10
#use delay(crystal=4MHz)

#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT

#define LEDA    PIN_C0
#define LEDB    PIN_C1
#define LEDC    PIN_C2
#define LEDD    PIN_C3
#define LEDE    PIN_C4
#define LEDF    PIN_C5
#define LEDG    PIN_C6

#define LEDA2    PIN_D0
#define LEDB2    PIN_D1
#define LEDC2    PIN_D2
#define LEDD2    PIN_D3
#define LEDE2    PIN_D4
#define LEDF2    PIN_D5
#define LEDG2    PIN_D6

void clearDisplay(int flag){

    if(flag) {
        output_high(LEDA);
        output_high(LEDB);
        output_high(LEDC);
        output_high(LEDD);
        output_high(LEDE);
        output_high(LEDF);
        output_high(LEDG);
    } else {
        output_high(LEDA2);
        output_high(LEDB2);
        output_high(LEDC2);
        output_high(LEDD2);
        output_high(LEDE2);
        output_high(LEDF2);
        output_high(LEDG2);
    }
}

void choose(int un, int dec) {
    switch (un)
    {
    case 0:
        output_low(LEDA);
        output_low(LEDB);
        output_low(LEDC);
        output_low(LEDD);
        output_low(LEDE);
        output_low(LEDF);
        break;
    case 1:
        output_low(LEDB);
        output_low(LEDC);
        break;
    case 2:
        output_low(LEDA);
        output_low(LEDB);
        output_low(LEDD);
        output_low(LEDE);
        output_low(LEDG);
        break;
    case 3:
        output_low(LEDA);
        output_low(LEDB);
        output_low(LEDC);
        output_low(LEDD);
        output_low(LEDG);
        break;
    case 4:
        output_low(LEDB);
        output_low(LEDC);
        output_low(LEDF);
        output_low(LEDG);
        break;
    case 5:
        output_low(LEDA);
        output_low(LEDC);
        output_low(LEDD);
        output_low(LEDF);
        output_low(LEDG);
        break;
    case 6:
        output_low(LEDA);
        output_low(LEDC);
        output_low(LEDD);
        output_low(LEDE);
        output_low(LEDF);
        output_low(LEDG);
        break;
    case 7:
        output_low(LEDA);
        output_low(LEDB);
        output_low(LEDC);
        break;
    case 8:
        output_low(LEDA);
        output_low(LEDB);
        output_low(LEDC);
        output_low(LEDD);
        output_low(LEDE);
        output_low(LEDF);
        output_low(LEDG);
        break;
    case 9:
        output_low(LEDA);
        output_low(LEDB);
        output_low(LEDC);
        output_low(LEDD);
        output_low(LEDF);
        output_low(LEDG);
        break;
    default:
        break;
    }

    switch (dec)
    {
    case 0:
        output_low(LEDA2);
        output_low(LEDB2);
        output_low(LEDC2);
        output_low(LEDD2);
        output_low(LEDE2);
        output_low(LEDF2);
        break;
    case 1:
        output_low(LEDB2);
        output_low(LEDC2);
        break;
    case 2:
        output_low(LEDA2);
        output_low(LEDB2);
        output_low(LEDD2);
        output_low(LEDE2);
        output_low(LEDG2);
        break;
    case 3:
        output_low(LEDA2);
        output_low(LEDB2);
        output_low(LEDC2);
        output_low(LEDD2);
        output_low(LEDG2);
        break;
    case 4:
        output_low(LEDB2);
        output_low(LEDC2);
        output_low(LEDF2);
        output_low(LEDG2);
        break;
    case 5:
        output_low(LEDA2);
        output_low(LEDC2);
        output_low(LEDD2);
        output_low(LEDF2);
        output_low(LEDG2);
        break;
    case 6:
        output_low(LEDA2);
        output_low(LEDC2);
        output_low(LEDD2);
        output_low(LEDE2);
        output_low(LEDF2);
        output_low(LEDG2);
        break;
    case 7:
        output_low(LEDA2);
        output_low(LEDB2);
        output_low(LEDC2);
        break;
    case 8:
        output_low(LEDA2);
        output_low(LEDB2);
        output_low(LEDC2);
        output_low(LEDD2);
        output_low(LEDE2);
        output_low(LEDF2);
        output_low(LEDG2);
        break;
    case 9:
        output_low(LEDA2);
        output_low(LEDB2);
        output_low(LEDC2);
        output_low(LEDD2);
        output_low(LEDF2);
        output_low(LEDG2);
        break;
    default:
        break;
    }
}

void main()
{
    output_low(PIN_B4);
    output_low(PIN_B5);

    while(1)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                clearDisplay(1);
                clearDisplay(0);
                choose(j, i);
                delay_ms(500);
            }
        }
    }
}