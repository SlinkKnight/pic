#include <16F877A.h>
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

void main() {

    int Aant, Bant, A, B;
    int conta = 0;

    lcd_init();

    Aant = input(PIN_A0);
    Bant = input(PIN_A1);

    while (1) {

        A = input(PIN_A0);
        B = input(PIN_A1);

        if (!input(PIN_A2))
            conta = 0;

        if (A != Aant || B != Bant) {

            if (Aant == 0 && Bant == 0 && A == 0 && B == 1) {
                lcd_putc('\f');
                printf(lcd_putc, "Esquerda");
                conta--;
                printf(lcd_putc, "\nConta: %d", conta);
            }

            if (Aant == 0 && Bant == 0 && A == 1 && B == 0) {
                lcd_putc('\f');
                printf(lcd_putc, "Direita");
                conta++;
                printf(lcd_putc, "\nConta: %d", conta);
            }

            Aant = A;
            Bant = B;
        }
    }
}