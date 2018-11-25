#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);//address, width, height.

void setup()
{
  // initialize the LCD
  lcd.begin();
  lcd.backlight();

}

void loop()
{
  // put your main code here, to run repeatedly:
  lcd.print("Hello, world!");
  lcd.println("Temp- ");
  delay(1000);
  lcd.clear();
  delay(2000);  
}
