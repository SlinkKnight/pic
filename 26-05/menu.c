#include <16F877A.h>
#device adc=10
#use delay(crystal=4MHz)
#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT


#define ACT1     PIN_C7
#define ACT2     PIN_C6
#define ACT3     PIN_C5
#define ACT4     PIN_C4
#define ACT5     PIN_D3
#define ACT6     PIN_D2
#define TEST_PIN PIN_D0

int8 segs[11] = {
    //PT //C //D //E //F //G //A //B
    0b10000100, //0
    0b10111110, //1
    0b11001000, //2
    0b10011000, //3
    0b10110010, //4
    0b10010001, //5
    0b10000001, //6
    0b10111100, //7
    0b10000000, //8
    0b10010000, //9
    0b11100000 //P
};

int8 segUnd  = 0;
int8 segDez  = 0;
int8 minUnd  = 0;
int8 minDez  = 0;
int8 horaUnd = 0;
int8 horaDez = 0;
int8 contagem = 0;
long int i = 0;

void allOff() {
    output_high(ACT1);
    output_high(ACT2);
    output_high(ACT3);
    output_high(ACT4);
    output_high(ACT5);
    output_high(ACT6);
}

void clockRefresh() {

    allOff();
    output_b(segs[horaDez]);
    delay_us(20);
    output_low(ACT1);
    delay_ms(1);

    allOff();
    output_b(segs[horaUnd]);
    delay_us(20);
    output_low(ACT2);
    delay_ms(1);

    allOff();
    output_b(segs[minDez]);
    delay_us(20);
    output_low(ACT3);
    delay_ms(1);

    allOff();
    output_b(segs[minUnd]);
    delay_us(20);
    output_low(ACT4);
    delay_ms(1);

    allOff();
    output_b(segs[segDez]);
    delay_us(20);
    output_low(ACT5);
    delay_ms(1);

    allOff();
    output_b(segs[segUnd]);
    delay_us(20);
    output_low(ACT6);
    delay_ms(1);

    allOff();
}

void menuRefresh() {

    allOff();

    output_low(ACT6);
    output_b(segs[contagem]);
    delay_ms(5);
    output_high(ACT6);

    output_low(ACT1);
    output_b(segs[10]);
    delay_ms(5);
    output_high(ACT1);
}

void testes() {
    int16 i;
    
    for(i = 0; i < 500; i++) {
        output_low(ACT1);
        output_b(segs[8]);
        delay_ms(5);
        output_high(ACT1);

        output_low(ACT2);
        output_b(segs[8]);
        delay_ms(5);
        output_high(ACT2);

        output_low(ACT3);
        output_b(segs[8]);
        delay_ms(5);
        output_high(ACT3);

        output_low(ACT4);
        output_b(segs[8]);
        delay_ms(5);
        output_high(ACT4);

        output_low(ACT5);
        output_b(segs[8]);
        delay_ms(5);
        output_high(ACT5);

        output_low(ACT6);
        output_b(segs[8]);
        delay_ms(5);
        output_high(ACT6);
    }
}

void incrementCount() {
    static int1 botaoUpAnt = 1;
    static int1 botaoDownAnt = 1;

    int1 botaoUpAtual   = input(PIN_A2);
    int1 botaoDownAtual = input(PIN_A1);

    if(botaoUpAnt == 1 && botaoUpAtual == 0) {
        contagem++;
        if(contagem > 9) contagem = 0;
    }

    if(botaoDownAnt == 1 && botaoDownAtual == 0) {
        if(contagem == 0) contagem = 9;
        else contagem--;
    }

    botaoUpAnt   = botaoUpAtual;
    botaoDownAnt = botaoDownAtual;
}

#INT_TIMER0
void interrupt_t0() {
    clear_interrupt(INT_TIMER0);
    set_timer0(6);
    if(i == 1000) {
        segUnd++;
        i = 0;
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
    i++;
}

void main() {

    int1 menuFlag = 0;
    int1 botaoAnterior = 1;
    int1 botaoAtual;

    enable_interrupts(GLOBAL);
    enable_interrupts(INT_TIMER0);
    setup_timer_0(T0_INTERNAL | T0_DIV_4);
    set_timer0(6);

    //testes();

    while(1) {
        output_low(TEST_PIN);

        botaoAtual = input(PIN_A0);

        if(botaoAnterior == 1 && botaoAtual == 0) menuFlag = !menuFlag;

        botaoAnterior = botaoAtual;

        if(!menuFlag) clockRefresh();
        else menuRefresh();

        incrementCount();

        output_high(TEST_PIN);
    }
}