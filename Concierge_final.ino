#include <LiquidCrystal_I2C.h>
#include <HX711.h>
#include "motor.h"
#include <SoftwareSerial.h>
#define pinDT  2
#define pinSCK  3
#define pinRx 5
#define pinTx 6

HX711 scale;
float peso = 0;
char comando;
LiquidCrystal_I2C lcd(0x27,20,4);
SoftwareSerial btSerial(pinRx, pinTx); // RX, TX

void setup() 
{
  lcd.init();
  lcd.backlight();
  lcd.begin(20, 4);
  scale.begin(pinDT, pinSCK); 
  scale.set_scale(427512); 
  delay(2000);
  scale.tare(); 
  Serial.begin(9600);
  btSerial.begin(9600);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  Serial.println("Fim Setup");
  delay(2000);
}

void loop() 
{
  if (btSerial.available())
  {
    comando = btSerial.read();
  }

  switch (comando)
  {
    case 'F': 
    {
        moveFrente();
        break;
      }
    case 'R': 
    {
        direita();
        break;
      }
    case 'L': 
    {
        esquerda();
        break;
      }
    case 'B': 
    {
        moveRe();
        break;
      }
    case 'W':
    {
      ativa_balanca();
      break;
    }
    default: 
    {
        parar();
        break;
      }
  }
}

void ativa_balanca()
{
 peso = scale.get_units(1); 
 delay(500); 
 if (peso > 1.5)
 {
  lcd.setCursor(0,0);
  lcd.print("  EXCESSO DE PESO!");
  lcd.setCursor(0,1);
  lcd.print("  POR FAVOR, RETIRE");
  lcd.setCursor(0,2);
  lcd.print("  O EXCESSO DE PESO");
  lcd.setCursor(0,3);
  lcd.print("                         ");
 }
  else
  {
  lcd.setCursor(0,0);
  lcd.print("                         ");
  lcd.setCursor(0,1);
  lcd.print("                         ");
  lcd.setCursor(0,2);
  lcd.print("                         ");
  lcd.setCursor(0,3);
  lcd.print("Peso em kg: ");
  lcd.print(peso, 2);
  }
}
