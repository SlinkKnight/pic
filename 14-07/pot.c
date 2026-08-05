#include <16F877A.h>
#device adc=10
#use delay(crystal=4MHz)
#FUSES NOPUT, NOBROWNOUT, NOLVP , HS, NOWDT

#define LCD_RS_PIN      PIN_D7
#define LCD_RW_PIN      PIN_D6
#define LCD_ENABLE_PIN  PIN_D5
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D3
#define LCD_DATA6       PIN_D2
#define LCD_DATA7       PIN_D1

#include <lcd.c>

float leituraADC;

void main()
{

setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);

   lcd_init();

   while (1)
   {
      leituraADC = read_adc();
      printf(lcd_putc,"\fValor: %2.2f", leituraADC);
      printf(lcd_putc,"\nTESTE OK");
      delay_ms(1000);
   }
}