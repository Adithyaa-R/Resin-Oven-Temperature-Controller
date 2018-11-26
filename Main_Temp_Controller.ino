#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <Adafruit_Sensor.h>
//#include <DHT.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);//address, width, height.
int TargetTemp = 0;
int CurrTemp = 0;
int CurrHum = 0;

int TempMin = 15;
int TempMax = 80;

int UpdateFreq = 5 * 1000;//seconds x millis
int lastUpdate = 0 - UpdateFreq;//subtracts the first update length so it runs first time.

void setup()
{
  // initialize the LCD
  lcd.begin();
  lcd.backlight();

}

void loop()
{
  // put your main code here, to run repeatedly:
  if (millis() > lastUpdate + UpdateFreq)
  {
    lastUpdate = millis();
    SetTemp();
    ReadTempDS18();
    //ReadTempDHT();
    LCD_Update();
    Heater();
  }
}

void SetTemp()
{
  TargetTemp = map(analogRead(3), 0, 1023, TempMin, TempMax);
  TargetTemp = constrain(TargetTemp, TempMin, TempMax);
}

void LCD_Update()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp=");
  lcd.setCursor(6, 0);
  lcd.print("xx");//info

  lcd.setCursor(10, 0);
  lcd.print("H=");//humidity label
  lcd.setCursor(13, 0);
  lcd.print("xx");

  lcd.setCursor(0, 1);
  lcd.print("Target=");
  lcd.setCursor(8, 1);
  lcd.print(TargetTemp);
}

void ReadTempDS18()
{

}

void ReadTempDHT()
{

}

void Heater()
{

}
