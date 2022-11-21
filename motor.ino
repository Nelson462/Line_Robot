#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C Address 0x27

int count = 0;
int sensorValue = 0;    //value read from the pot
int outputValue = 0;    //value putput to the PVM (analog out)

void setup() {
   Serial.begin(9600);
   pinMode(4, INPUT_PULLUP);
   pinMode(5, INPUT_PULLUP);
   pinMode(6, INPUT_PULLUP);
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(7,HIGH);
}

void loop() {
  digitalWrite(7,HIGH);
  if(digitalRead(6) == 0)
  {
    if (digitalRead(4) == 0)
    {
      count = count + 50;
      if(count > 255)
      count = 255;
      delay(200);
    }
    else if(digitalRead(5) == 0)
    {
      count = count - 50;
      if(count < 0);
         count = 0 ;
    }

    digitalWrite(2, LOW);
    analogWrite(3, count);
  }
  else
  {
    //tead the analog in value;
    sensorValue = analogRead(A0);
    // map it to the range of the analog out;
    outputValue = map(sensorValue, 0, 1023, 0, 255);
    // change the analog out value;
    Serial.println(outputValue);
    digitalWrite(2, LOW);
    analogWrite(3, outputValue);
  }
  Display_LCD();
}
void Display_LCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  //Show Temperature
  lcd.setCursor(0, 0);
  lcd.print("PWM: ");
  lcd.setCursor(7,0);
  lcd.print(outputValue);
  
  
  lcd.setCursor(0, 1);
  lcd.print("Button: ");
  lcd.setCursor(7,1);
  lcd.print(sensorValue);
}
