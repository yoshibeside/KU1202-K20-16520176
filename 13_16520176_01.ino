#include<LiquidCrystal.h>
LiquidCrystal lcd (7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello,world!");
}

void loop(){
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
}