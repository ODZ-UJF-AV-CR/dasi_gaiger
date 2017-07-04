/* GM-couter for Dasa 

Counter library: http://www.pjrc.com/teensy/td_libs_FreqCount.html

Aruino 	ATmega8DIL01A 	Note
D0 	RXD 	PD0, if you disconnect USB232R01B
D1 	TXD 	PD1, if you disconnect USB232R01B
D2 	PD2	Digital I/Os.
D3/PWM 	PD3
D4 	PD4
D5/PWM 	PD5      Counter input
D6/PWM 	PD6
D7 	PD7
D8 	PB0
D9/PWM 	PB1
D10/PWM 	PB2
D11/PWM 	PB3
D12 	PB4
D13 	PB5
A0 	PC0 	Analog inputs.
A1 	PC1
A2 	PC2
A3 	PC3
A4 	PC4
A5 	PC5
*/

#include <FreqCount.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

void setup() 
{
  Serial.begin(9600);
  FreqCount.begin(1000);

  lcd.init();                      // initialize the lcd 
 
  //lcd.backlight();

  lcd.print("Cvak...");
  delay(1000);          
  lcd.print("Hmmm...");
  delay(1000);            
  lcd.clear();
}

int sum = 0;
int minute = 0;

void loop() 
{
  if (FreqCount.available()) 
  {
    unsigned long count = FreqCount.read();
    Serial.println(count);
    lcd.setCursor ( 0, 0 );
    lcd.print(count);
    lcd.print("   ");
    lcd.setCursor ( 4, 0 );
    lcd.print("CPS");
    lcd.setCursor ( 0, 1 );
    if(count>25)
    {
      lcd.print("Daso utikej!!!!!");
      lcd.backlight();
      delay(300);            
      lcd.noBacklight();
      delay(200);            
    }
    else
    {
      lcd.print("Dasa je v pohode");
    };
    sum += count;
    minute++;
  }
  
  if (minute>=60)
  {
    lcd.setCursor ( 8, 0 );
    lcd.print("     CPM");
    lcd.setCursor ( 8, 0 );
    lcd.print(sum);
    sum = 0;
    minute = 0;
  }
}

