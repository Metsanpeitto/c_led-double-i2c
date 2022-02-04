
#include <Wire.h>
#include <I2C_Anything.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x26, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const byte SLAVE_ADDRESS = 42;

// Receive variables
volatile boolean haveData = false;
volatile float temp;
volatile float ph;
volatile float ec;
int value1 = 00000000;
int value2 = 00000000;
void setup()
{
  Wire.begin ();
  Wire.onReceive (receiveEvent);   
  lcd.begin(16, 2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light  
  lcd.clear();
  lcd.print("-----Works-----");
  delay(4000);
    
  requestValues(); 
}  // end of setup

void loop()
{
requestValues();
    delay (4000);
  // end of for

}  // end of loop

void setRelays() {
      int comand = 0;
       Wire.beginTransmission (SLAVE_ADDRESS);
      I2C_writeAnything (comand);
      Wire.endTransmission();
  }


void requestValues() {
      int comand = 0;
       Wire.beginTransmission (SLAVE_ADDRESS);
      I2C_writeAnything (comand);
      Wire.endTransmission();
  }

// called by interrupt service routine when incoming data arrives
void receiveEvent (int howMany)
 {
 if (howMany >= (sizeof ph) + (sizeof ec) + (sizeof temp))
   {
   I2C_readAnything (ph);
   I2C_readAnything (ec);
   I2C_readAnything (temp);  
   lcd.clear();
   lcd.print(F("ph"));
   lcd.setCursor(0, 2);
   lcd.write(ph); 
   lcd.clear();
   lcd.print(F("ec"));
   lcd.setCursor(0, 2);
   lcd.write(ec); 
   lcd.clear();
   lcd.print(F("temp"));
   lcd.setCursor(0, 2);
   lcd.write(temp); 
   
   
   haveData = true;
   }  // end if have enough data
 }  // end of receiveEvent
