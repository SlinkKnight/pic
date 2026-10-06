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

#define TAMANHO 16 
#define LIMITE_DIGITOS 16 
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

int32 valor1Int = 0, valor2Int = 0, resultadoInt = 0; 
float valor1Float = 0, valor2Float = 0, resultadoFloat = 0; 
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
   valor1Int = 0; 
   valor2Int = 0; 
   resultadoInt = 0; 
   valor1Float = 0; 
   valor2Float = 0; 
   resultadoFloat = 0; 
   usaFloat = FALSE; 
   flagErro = 0; 
} 

int1 estouraIntounadahaver(char op, int32 a, int32 b) 
{ 
   switch (op) { 
      case '+': 
         return (a > (MAX_VAL_INT - b)); 
      case '-': 
         return (a < b); 
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

int1 estouraFloatounadahaver(char op, float a, float b) 
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
               int8 digito; 
               int1 overflowNaLeitura = FALSE; 
               valor1Int = 0; 
               for (i = 0; i < casasAntes && !overflowNaLeitura; i++) { 
                  digito = numero1[i] - '0'; 
                  if (valor1Int > (MAX_VAL_INT - digito) / 10) { 
                     overflowNaLeitura = TRUE; 
                  } else { 
                     valor1Int = valor1Int * 10 + digito; 
                  } 
               } 

               valor2Int = 0; 
               for (i = 0; i < casasDepois && !overflowNaLeitura; i++) { 
                  digito = numero2[i] - '0'; 
                  if (valor2Int > (MAX_VAL_INT - digito) / 10) { 
                     overflowNaLeitura = TRUE; 
                  } else { 
                     valor2Int = valor2Int * 10 + digito; 
                  } 
               } 

               if (overflowNaLeitura) { 
                  flagErro = 2;
               } 
               else if (operador == '/' && valor2Int == 0) { 
                  flagErro = 1; 
               } 
               else if (estouraIntounadahaver(operador, valor1Int, valor2Int)) { 
                  flagErro = 2; 
               } 
               else { 
                  switch (operador) { 
                     case '+': resultadoInt = valor1Int + valor2Int; break; 
                     case '-': resultadoInt = valor1Int - valor2Int; break; 
                     case '*': resultadoInt = valor1Int * valor2Int; break; 
                     case '/': resultadoInt = valor1Int / valor2Int; break; 
                     default: resultadoInt = valor1Int + valor2Int; break; 
                  } 
               } 
            } 
            else { 
               int1 overflowFloatLeitura = FALSE;

               fimInteira = (ponto1 == -1) ? casasAntes : ponto1; 
               valor1Float = 0; 
               for (i = 0; i < fimInteira; i++) {
                  if (valor1Float > (MAX_VAL_FLOAT - (numero1[i] - '0')) / 10.0) {
                     overflowFloatLeitura = TRUE;
                     break;
                  }
                  valor1Float = valor1Float * 10 + (numero1[i] - '0'); 
               }

               if (ponto1 != -1 && !overflowFloatLeitura) { 
                  frac = 0.1; 
                  for (i = ponto1; i < casasAntes; i++) { 
                     valor1Float = valor1Float + (numero1[i] - '0') * frac; 
                     frac = frac / 10; 
                  } 
               } 

               fimInteira = (ponto2 == -1) ? casasDepois : ponto2; 
               valor2Float = 0; 
               for (i = 0; i < fimInteira; i++) { 
                  if (valor2Float > (MAX_VAL_FLOAT - (numero2[i] - '0')) / 10.0) {
                     overflowFloatLeitura = TRUE;
                     break;
                  }
                  valor2Float = valor2Float * 10 + (numero2[i] - '0'); 
               } 

               if (ponto2 != -1 && !overflowFloatLeitura) { 
                  frac = 0.1; 
                  for (i = ponto2; i < casasDepois; i++) { 
                     valor2Float = valor2Float + (numero2[i] - '0') * frac; 
                     frac = frac / 10; 
                  } 
               } 

               if (overflowFloatLeitura) {
                  flagErro = 2;
               }
               else if (operador == '/' && valor2Float == 0) { 
                  flagErro = 1; 
               } 
               else if (estouraFloatounadahaver(operador, valor1Float, valor2Float)) { 
                  flagErro = 2; 
               } 
               else { 
                  switch (operador) { 
                     case '+': resultadoFloat = valor1Float + valor2Float; break; 
                     case '-': resultadoFloat = valor1Float - valor2Float; break; 
                     case '*': resultadoFloat = valor1Float * valor2Float; break; 
                     case '/': resultadoFloat = valor1Float / valor2Float; break; 
                     default: resultadoFloat = valor1Float + valor2Float; break; 
                  } 
               } 
            } 

            lcd_putc("\f"); 
            if(flagErro == 0) { 
               lcd_gotoxy(1, 1); 
               printf(lcd_putc, "Res:"); 
               lcd_gotoxy(1, 2); 
               if (!usaFloat) { 
                  printf(lcd_putc, "%ld", resultadoInt); 
               } else { 
                  printf(lcd_putc, "%.5f", resultadoFloat); 
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
               if (ponto1 == -1 && casasAntes < LIMITE_DIGITOS) 
                  ponto1 = casasAntes; 
            } 
            else { 
               if (ponto2 == -1 && casasDepois < LIMITE_DIGITOS) 
                  ponto2 = casasDepois; 
            } 
         } 
         else if (letra >= '0' && letra <= '9') { 
            if (!operadorFlag) { 
               if ((casasAntes + (ponto1 != -1 ? 1 : 0)) < LIMITE_DIGITOS) { 
                  numero1[casasAntes] = letra; 
                  casasAntes++; 
               }
            } 
            else { 
               if ((casasDepois + (ponto2 != -1 ? 1 : 0)) < LIMITE_DIGITOS) { 
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

         lcd_gotoxy(1, 2); 
         printf(lcd_putc, "%s", display2); 

         delay_ms(100); 
      } 
   } 
}