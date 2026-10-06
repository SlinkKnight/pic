#include <16F877A.h>
#device adc=8
#use delay(crystal=4MHz)

#FUSES NOPUT, NOBROWNOUT, NOLVP, HS, NOWDT

#define saida PIN_C2
#define clock 0
#define div 5

int1 state = 0;

#INT_TIMER0
void interrupt_t0(void)
{
   set_timer0(127);
   
   state = !state;
   
   if (state) {
      output_high(saida); 
   } else {
      output_low(saida); 
   }
}

void main()
{
   setup_timer_0(clock | div);
   set_timer0(127);

   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);

   while (1)
   {      
      delay_ms(100);
   }
}