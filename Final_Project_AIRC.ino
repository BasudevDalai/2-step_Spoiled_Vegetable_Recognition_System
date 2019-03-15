//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
  return celsius + 273.15;
}

#include "MQ135.h"
#define ANALOGPIN A1    //  Define Analog PIN on Arduino Board
#define RZERO 206.85    //  Define RZERO Calibration Value
MQ135 gasSensor = MQ135(ANALOGPIN);

#include <DHT11.h>
#include <LiquidCrystal.h>

dht11 DHT11;

#define DHT11PIN A0
LiquidCrystal lcd(12,11,5,4,3,2);

void setup()
{
  float rzero = gasSensor.getRZero();
  Serial.print("MQ135 RZERO Calibration Value : ");
  Serial.println(rzero);

  Serial.begin(9600);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  lcd.clear();
  lcd.begin(16,2);
}

void loop()
{
  
  Serial.println("\n");
  
  MQ135 gasSensor = MQ135(A1);
  float air_quality = gasSensor.getPPM();
  float ppm = gasSensor.getPPM();

  delay(1000);
  digitalWrite(13,HIGH);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
  lcd.setCursor (0, 0);
  lcd.print (" AQ is ");
  lcd.print (air_quality);
  lcd.print (" PPM ");
  lcd.setCursor (0,1); 
  lcd.scrollDisplayLeft();
  delay(1000);

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case 0: Serial.println("OK"); break;
    case -1: Serial.println("Checksum error"); break;
    case -2: Serial.println("Time out error"); break;
    default: Serial.println("Unknown error"); break;
  }

  Serial.print("Humidity(%): ");
  Serial.println((float)DHT11.humidity, A0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.setCursor(0,1);
  lcd.print((float)DHT11.humidity, A0);
  lcd.print("%");
  delay(1000);

  Serial.print("Temperature(oC): ");
  Serial.println((float)DHT11.temperature, A0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.setCursor(0,1);
  lcd.print((float)DHT11.temperature, A0);
  lcd.print("oC");
  delay(1000);

  
}
