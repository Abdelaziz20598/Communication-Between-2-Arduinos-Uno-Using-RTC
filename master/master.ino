#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void setup (void) {
 while (!Serial); 
 Serial.begin(9600); 
 Serial.println("This is the Master");
 if (! rtc.begin()) {
   Serial.println("Couldn't find RTC");
      while (1);
 }
 if (! rtc.isrunning()) {
   Serial.println("RTC is NOT running!");
   // following line sets the RTC to the date & time this sketch was compiled
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   // This line sets the RTC with an explicit date & time, for example to set
   // January 21, 2014 at 3am you would call:
   // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
 }

/* ********************** */
   digitalWrite(SS, HIGH); // disable Slave Select
   SPI.begin ();
   SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
}
/*******************/
void loop () {
  
 DateTime now = rtc.now();
 Serial.print(now.year(), DEC);
 Serial.print('/');
 Serial.print(now.month(), DEC);
 Serial.print('/');
 Serial.print(now.day(), DEC);
 Serial.print(" <");
 Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
 Serial.print("> ");
 Serial.print(now.hour(), DEC);
 Serial.print(':');
 Serial.print(now.minute(), DEC);
 Serial.print(':');
 Serial.println(now.second(), DEC);
 delay(1000);
   digitalWrite(SS, LOW); // enable Slave Select
   // send test string
    String x;
    x=String(now.year())+"/" +String(now.month())+"/"+ String(now.day())+" <"+daysOfTheWeek[now.dayOfTheWeek()]+"> "+String(now.hour())+":"+String(now.minute())+":"+String(now.second())+'O' ;
   
    for ( int i =0 ;i <= x.length(); i++) {
      SPI.transfer(x[i]);
      
      delay(100);
   }
   digitalWrite(SS, HIGH); // disable Slave Select
   delay(3000);
}
