#include <16F877A.h>

#device adc=10
#use delay(crystal=4MHz)
#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT

void main() {

    output_high(PIN_B1);
    delay_cycles(5);
    while(input(PIN_A0));
    output_low(PIN_B1);

}

