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

#define TAMANHO 8
#define MAX_VAL_INT 2147483647L
#define MAX_VAL_FLOAT 3.4e38

char numero1[TAMANHO] = {0};
char numero2[TAMANHO] = {0};
char display1[19] = {0};
char display2[19] = {0};
char operador = 0;
int1 operadorFlag = FALSE;
int8 flagErro = 0;

int casasAntes = 0, casasDepois = 0;
int ponto1 = -1, ponto2 = -1;

int32 valor1_int = 0, valor2_int = 0, resultado_int = 0;
float valor1_float = 0, valor2_float = 0, resultado_float = 0;
int1 usaFloat = FALSE;

char letra;
int i, j;
float frac;
int fimInteira;

void clean(void)
{
   for (i = 0; i < TAMANHO; i++)
   {
      numero1[i] = 0;
      numero2[i] = 0;
   }
   casasAntes = 0;
   casasDepois = 0;
   ponto1 = -1;
   ponto2 = -1;
   operador = 0;
   operadorFlag = FALSE;
   valor1_int = 0;
   valor2_int = 0;
   resultado_int = 0;
   valor1_float = 0;
   valor2_float = 0;
   resultado_float = 0;
   usaFloat = FALSE;
   flagErro = 0;
}

int1 estourarInt(char op, int32 a, int32 b)
{
   switch (op) {
      case '+':
         return (a > (MAX_VAL_INT - b));
      case '-':
         return (a < b); // Como só temos positivos, se a < b gera resultado negativo (inválido)
      case '*':
         if (a == 0 || b == 0) return FALSE;
         return (a > (MAX_VAL_INT / b));
      case '/':
         if (b == 0) return TRUE;
         return FALSE;
      default:
         return FALSE;
   }
}

int1 estourarFloat(char op, float a, float b)
{
   switch (op) {
      case '+':
         return ((MAX_VAL_FLOAT - a) < b);
      case '-':
         return (a < b);
      case '*':
         if (a == 0 || b == 0) return FALSE;
         return (a > (MAX_VAL_FLOAT / b));
      case '/':
         if (b == 0) return TRUE;
         return (a > (MAX_VAL_FLOAT * b));
      default:
         return FALSE;
   }
}

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

   clean();
   lcd_putc("\f");

   while (TRUE) {
      letra = kbd_getc();

      if (letra != 0) {
         delay_ms(1);

         if (letra == '#') {
            usaFloat = (ponto1 != -1 || ponto2 != -1);

            if (!usaFloat) {
               valor1_int = 0;
               for (i = 0; i < casasAntes; i++)
                  valor1_int = valor1_int * 10 + (numero1[i] - '0');

               valor2_int = 0;
               for (i = 0; i < casasDepois; i++)
                  valor2_int = valor2_int * 10 + (numero2[i] - '0');

               if (operador == '/' && valor2_int == 0) {
                  flagErro = 1;
               }
               else if (estourarInt(operador, valor1_int, valor2_int)) {
                  flagErro = 2;
               }
               else {
                  switch (operador) {
                     case '+': resultado_int = valor1_int + valor2_int; break;
                     case '-': resultado_int = valor1_int - valor2_int; break;
                     case '*': resultado_int = valor1_int * valor2_int; break;
                     case '/': resultado_int = valor1_int / valor2_int; break;
                     default: resultado_int = valor1_int + valor2_int; break;
                  }
               }
            }
            else {
               int32 tempInt1 = 0;
               fimInteira = (ponto1 == -1) ? casasAntes : ponto1;
               for (i = 0; i < fimInteira; i++)
                  tempInt1 = tempInt1 * 10 + (numero1[i] - '0');

               valor1_float = (float)tempInt1;
               if (ponto1 != -1) {
                  frac = 0.1;
                  for (i = ponto1; i < casasAntes; i++) {
                     valor1_float = valor1_float + (numero1[i] - '0') * frac;
                     frac = frac / 10;
                  }
               }

               int32 tempInt2 = 0;
               fimInteira = (ponto2 == -1) ? casasDepois : ponto2;
               for (i = 0; i < fimInteira; i++)
                  tempInt2 = tempInt2 * 10 + (numero2[i] - '0');

               valor2_float = (float)tempInt2;
               if (ponto2 != -1) {
                  frac = 0.1;
                  for (i = ponto2; i < casasDepois; i++) {
                     valor2_float = valor2_float + (numero2[i] - '0') * frac;
                     frac = frac / 10;
                  }
               }

               if (operador == '/' && valor2_float == 0) {
                  flagErro = 1;
               }
               else if (estourarFloat(operador, valor1_float, valor2_float)) {
                  flagErro = 2;
               }
               else {
                  switch (operador) {
                     case '+': resultado_float = valor1_float + valor2_float; break;
                     case '-': resultado_float = valor1_float - valor2_float; break;
                     case '*': resultado_float = valor1_float * valor2_float; break;
                     case '/': resultado_float = valor1_float / valor2_float; break;
                     default: resultado_float = valor1_float + valor2_float; break;
                  }
               }
            }

            lcd_putc("\f");
            if(flagErro == 0) {
               lcd_gotoxy(1, 1);
               printf(lcd_putc, "Res:");
               lcd_gotoxy(1, 2);
               if (!usaFloat) {
                  printf(lcd_putc, "%ld", resultado_int);
               } else {
                  printf(lcd_putc, "%.3f", resultado_float);
               }
            }
            else if(flagErro == 1){
               lcd_gotoxy(1, 1);
               printf(lcd_putc, "Erro:");
               lcd_gotoxy(1, 2);
               printf(lcd_putc, "Divisao por zero");
            } 
            else if(flagErro == 2){
               lcd_gotoxy(1, 1);
               printf(lcd_putc, "Erro:");
               lcd_gotoxy(1, 2);
               printf(lcd_putc, "Overflow");
            }
            
            delay_ms(3000);
            clean();
            lcd_putc("\f");
            continue;
         }

         else if (letra == '+' || letra == '-' || letra == '*' || letra == '/') {
            if (!operadorFlag) {
               operador = letra;
               operadorFlag = TRUE;
            }
         }
         else if (letra == '.') {
            if (!operadorFlag) {
               if (ponto1 == -1)
                  ponto1 = casasAntes;
            }
            else {
               if (ponto2 == -1)
                  ponto2 = casasDepois;
            }
         }
         else if (letra >= '0' && letra <= '9') {
            if (!operadorFlag) {
               // Corrigido para respeitar o limite seguro do TAMANHO 8 (max 7 dígitos)
               if (casasAntes < (TAMANHO - 1)) {
                  numero1[casasAntes] = letra;
                  casasAntes++;
               }
            }
            else {
               if (casasDepois < (TAMANHO - 1)) {
                  numero2[casasDepois] = letra;
                  casasDepois++;
               }
            }
         }

         j = 0;
         for (i = 0; i <= casasAntes; i++) {
            if (i == ponto1 && ponto1 != -1) {
               display1[j] = '.';
               j++;
            }
            if (i < casasAntes) {
               display1[j] = numero1[i];
               j++;
            }
         }
         display1[j] = 0;

         j = 0;
         for (i = 0; i <= casasDepois; i++) {
            if (i == ponto2 && ponto2 != -1) {
               display2[j] = '.';
               j++;
            }
            if (i < casasDepois) {
               display2[j] = numero2[i];
               j++;
            }
         }
         display2[j] = 0;

         lcd_putc("\f");
         
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "%s", display1);
         if (operador != 0) {
            lcd_gotoxy(16, 1);
            printf(lcd_putc, "%c", operador);
         }

         lcd_gotoxy(1, 2);
         printf(lcd_putc, "%s", display2);

         delay_ms(100);
      }
   }
}