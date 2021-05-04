#include<LiquidCrystal.h>

LiquidCrystal lcd (7,6,5,4,3,2);		//pinArduino terhubung LCD
const int pingPin = A1;				//pin Arduino terhubung Ultrasonic
long dur, cm;							// simpan nilai durasi dan jarak (cm)

void setup(){
  lcd.begin(16,2);						//atur jumlah kolom dan baris LCD
  lcd.print("Ping Sensor");
}

void loop(){
  cm=read_sensor_ultrasonic();
  
  lcd.setCursor(0,1);					// atur kursor ke kolom 0 baris 1
  lcd.print("Jarak ");
  lcd.setCursor(6,1);					// atur kursor ke kolom 6 baris 1
  lcd.print(cm);						// cetak nilai jarak
  print_unit_cm(cm);					// cetak satuan (cm)
}

int read_sensor_ultrasonic(){
  pinMode(pingPin, OUTPUT);				// atur pin sebagai OUTPUT
  digitalWrite(pingPin, LOW);			// beri sinyal awal LOW
  delayMicroseconds(2);					// jeda 2 us
  digitalWrite(pingPin,HIGH);			// trigger sensor dengan sinyal HIGH
  delayMicroseconds(5);					// trigger sensor selama 5 us
  digitalWrite(pingPin, LOW);			// beri sinyal LOW
  
  pinMode(pingPin, INPUT);				// atur pin sebagai INPUT
  dur = pulseIn(pingPin, HIGH);			// sinyal HIGH untuk dapat durasi
  cm = microsecondsToCentimeters(dur);	// konversi us ke cm

  if (cm >= 2 && cm <=300){
    return cm;
  } else {
    return 0;
  }
}

long microsecondsToCentimeters(long ms){
  // kecepatan suara 340 cm/s atau 29 us/cm
  // dibagi dua untuk mencari jarak sensor-objek
  return ms/29/2;
}

void print_unit_cm(long cm){
  
  int ROW = 1;							//nomor baris
  int ERR_Digit = 6;					// koordinat kolom
  int oneDigit = 7;						// koordinat kolom
  int twoDigit = 8;						// koordinat kolom
  int threeDigit=9;						// koordinat kolom
  int lenUnit= 2;						// jumlah karakter satuan
  
  if (cm>=2 && cm < 10){				// jarak 2-9 cm
    lcd.setCursor(oneDigit,ROW);		// atur posisi kursor
    lcd.print("cm");
    print_blank(oneDigit + lenUnit, ROW); // jarak 10-99 cm
  } else if (cm >=10 && cm < 100){		// atur posisi kursor
    lcd.setCursor(twoDigit,ROW);
    lcd.print("cm");
    print_blank(twoDigit + lenUnit,ROW);
  } else if (cm >=100 && cm < 330){		// jarak 100- 329 cm
    lcd.setCursor(threeDigit,ROW);		// atur posisi kursor
    lcd.print("cm");
    print_blank(threeDigit + lenUnit,ROW);
  } else {
    lcd.setCursor(ERR_Digit,ROW);		// bukan dalam range jarak yang diukur
    print_blank(ERR_Digit,ROW);			// posisi kursor diatur kalau kasus luar jarak range ukur
  }
}

void print_blank(int col, int row){
  /* cetak spasi/blank sampai kolom ke-16*/
  
  int total_col = 16;
  for (int i = col; i< total_col; i ++){
    lcd.setCursor(i,row);
    lcd.print(" ");
  }
}
    
    
    