#include <SPI.h>
char s_recv="";
volatile boolean process_flag ;
void setup (void) {
  while (!Serial); 
   Serial.begin (9600);
   Serial.println("this is the slave");
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   
   // SPI slave mode
   SPCR |= _BV(SPE); // turn on SPI in slave mode  SPCR = (1<<SPE)| (1<<SPIE);
   process_flag = false;
   SPI.attachInterrupt(); // turn on interrupt
}
ISR (SPI_STC_vect) {// SPI interrupt routine 
   s_recv =  SPDR; // read byte from SPI Data Register
      process_flag = true;
   }


void loop (void) {
   if (process_flag) {
      if(s_recv!='O'){
        
      Serial.print(s_recv); //print the array on serial monitor
      }
      else{Serial.println();}
     
      process_flag = false; //reset the process
  
   }
   
}
