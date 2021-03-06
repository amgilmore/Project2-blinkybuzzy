#include <msp430.h>

#include "libTimer.h"

#include "buzzer.h"

void buzzer_init()

{

  /* 

       Direct timer A output "TA0.1" to P2.6.  

        According to table 21 from data sheet:

          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero

          P2SEL.6 must be 1

        Also: P2.6 direction must be output

  */

  timerAUpmode();/* used to drive speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */

{
  CCR0 = cycles;
  CCR1 = cycles >> 1;/* one half cycle */
}

void play_beep() {
  buzzer_set_period(750);
  __delay_cycles(5000000);
  buzzer_set_period(0); // silence buzzer

  return;

}

void play_song() {
  short E = 750;
  short C = 950;
  short G = 630;
  short lowG = 1260;

  
  int mario[10] = {E,C,G,lowG,0,E,C,G,lowG,0}


  for (int i = 0; i < 10; i++) {
    buzzer_set_period(mario[i]);
    __delay_cycles(5000);

  }
  buzzer_set_period(0); // period set to 0, silences buzzer
  return;

}
