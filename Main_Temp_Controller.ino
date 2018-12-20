#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <DHT.h>


#include <OneWire.h>
#include <DS18B20.h>
#define ONE_WIRE_BUS 4 //originally 2
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);


LiquidCrystal_I2C lcd(0x3F, 16, 2);//address, width, height.
//DHT dht;

int TargetTemp = 0;
int CurrTemp = 0;
int CurrHum = 0;

int Hyst = 3;//the hysterisis of the temperature.
int TempMin = 15;
int TempMax = 80;

int UpdateFreq = 5 * 1000;//seconds x millis //don't set below 1-2s, depending on temp sensor
int lastUpdate = 0 - UpdateFreq;//subtracts the first update length so it runs first time.

//pins
int relayPin = 1;
int potPin = 3;
int DHTpin = 4;


void setup()
{
  // initialize the LCD
  lcd.begin();
  lcd.backlight();
  //dht.setup(DHTpin);
}

void loop()
{
  SetTemp();
  LCD_Update();
  if (millis() > lastUpdate + UpdateFreq)
  {
    lastUpdate = millis();
    SetTemp();
    ReadTempDS18();
    //ReadTempDHT();
    Heater();
  }
}

void SetTemp()
{
  TargetTemp = map(analogRead(potPin), 0, 1023, TempMin, TempMax);
  TargetTemp = constrain(TargetTemp, TempMin, TempMax);
}

void LCD_Update()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp=");
  lcd.setCursor(6, 0);
  lcd.print(CurrTemp);//info

  lcd.setCursor(10, 0);
  lcd.print("H=");//humidity label
  lcd.setCursor(13, 0);
  lcd.print(CurrHum);

  lcd.setCursor(0, 1);
  lcd.print("Target=");
  lcd.setCursor(8, 1);
  lcd.print(TargetTemp);
}

void ReadTempDS18()
{
  sensor.requestTemperatures();
  while (!sensor.isConversionComplete());  // wait until sensor is ready
  CurrTemp = sensor.getTempC();
}

void ReadTempDHT()
{
  //CurrHum = dht.getHumidity();
  //CurrTemp = dht.getTemperature();
}

void Heater()
{
  if(CurrTemp <= TargetTemp)
  {
    digitalWrite(relayPin, HIGH);
  }
  else if(CurrTemp >= (TargetTemp + Hyst))
  {
    digitalWrite(relayPin, LOW);    
  }
}
