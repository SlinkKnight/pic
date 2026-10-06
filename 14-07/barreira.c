#include <16F877A.h> 
#use delay(crystal=4MHz) 

#define use_portb_kbd TRUE 
#define LCD_DATA_PORT getenv("SFR:PORTD") 

#include <14-07\kbdlib.c> 
#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT 

#define LCD_RS_PIN      PIN_D7 
#define LCD_RW_PIN      PIN_D6 
#define LCD_ENABLE_PIN  PIN_D5 
#define LCD_DATA4       PIN_D4 
#define LCD_DATA5       PIN_D3 
#define LCD_DATA6       PIN_D2 
#define LCD_DATA7       PIN_D1 
#include <lcd.c> 

#define SENSOR_PIN      PIN_C0
#define SAIDA_PIN       PIN_C1

void main() 
{ 
   setup_adc_ports(NO_ANALOGS); 
   setup_adc(ADC_OFF); 
   setup_psp(PSP_DISABLED); 
   setup_spi(SPI_SS_DISABLED); 
   setup_timer_1(T1_DISABLED); 
   setup_timer_2(T2_DISABLED, 0, 1); 
   setup_comparator(NC_NC_NC_NC); 
   setup_vref(FALSE); 
   port_b_pullups(TRUE); 

   lcd_init(); 
   kbd_init(); 
   
   output_high(SAIDA_PIN);
   
   lcd_putc("\fDigite o num:\n"); 

   char caractere;
   int8 index = 0;
   int finalVal = 0;
   int valSalvo = 0;
   int contaSensor = 0;
   int1 sensorAnterior = 0;
   int1 sensorAtual;
   int1 digitando = TRUE;

   while (TRUE) { 
      caractere = kbd_getc();
      
      if (caractere != 0) {
         if (digitando) {
            if (caractere >= '0' && caractere <= '9') {
               if (index < 5) {
                  finalVal = (finalVal * 10) + (caractere - '0');
                  lcd_putc(caractere);
                  index++;
               }
            }
            else if (caractere == '#') {
               if (index > 0) {
                  valSalvo = finalVal;
                  sensorAnterior = input(SENSOR_PIN);
                  digitando = FALSE;
                  output_high(SAIDA_PIN);
                  
                  lcd_putc("\f");
                  contaSensor = 0;
                  printf(lcd_putc, "Alvo:%i\nCont:%i", valSalvo, contaSensor);
               }
            }
            else if (caractere == '*') {
               index = 0;
               finalVal = 0;
               lcd_putc("\fCancelado\n");
               delay_ms(1000);
               lcd_putc("\fDigite o num:\n");
            }
         }
         else {
            if (caractere == '*') {
               digitando = TRUE;
               index = 0;
               finalVal = 0;
               contaSensor = 0;
               output_high(SAIDA_PIN);
               lcd_putc("\fDigite o num:\n");
            }
         }
      }

      if (!digitando) {
         sensorAtual = input(SENSOR_PIN);
         if (sensorAtual == 1 && sensorAnterior == 0) {
            contaSensor++;
            
            lcd_putc("\f");
            printf(lcd_putc, "Alvo:%i\nCont:%i", valSalvo, contaSensor);

            if (contaSensor == valSalvo) {
               output_low(SAIDA_PIN);
            } else output_high(SAIDA_PIN);
         }
         sensorAnterior = sensorAtual;
      }
   }
}
