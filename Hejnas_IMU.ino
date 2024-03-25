//****************************************************************
//
//              ...:::  Hejnas IMU   :::...
//
//****************************************************************

#include <Wire.h>

byte LSM6DS3_ADDR = 0x6B;
String version = "v1.0";

//-------------------------
//    setup
//-------------------------
void setup() {

  //Procedura początkowa
  Wire.begin();
  Serial.begin(57600);
  delay(1000);
  Serial.print("\nHejnas IMU ");
  Serial.println(version);

  //Sprawdzenie czy na i2c jest podłączony LSM6DS3
  byte connectionStatus = CheckConnectionLSM6DS3();
  if(connectionStatus = true)Serial.println("LSM6DS3 connection OK");
  else {
    Serial.println("LSM6DS3 connection nOK");
    while(1);
  }

  // Konfiguracja akcelerometru
  Wire.beginTransmission(LSM6DS3_ADDR); // Rozpoczęcie transmisji do akcelerometru
  Wire.write(0x10);                     // Rejestr kontrolny dla konfiguracji
  Wire.write(0x43);                     // Ustawienia konfiguracyjne: 104 Hz ODR, ±2g range
  Wire.endTransmission();               // Zakończenie transmisji

  //Serial.println("accX;accY;accZ");
  
}//end of void setup()



//------------------------
//    loop
//------------------------
void loop() {

  // Odczyt danych akcelerometru
  Wire.beginTransmission(LSM6DS3_ADDR); // Rozpoczęcie transmisji do akcelerometru
  Wire.write(0x28);                     // Rejestr danych X akcelerometru (LSB)
  Wire.endTransmission(false);           // Zakończenie transmisji (false - bez stop bitu)

  Wire.requestFrom(LSM6DS3_ADDR, 6);    // Odczyt 6 bajtów danych (po 2 bajty na oś)
  if (Wire.available() >= 6) {
    int16_t x = Wire.read() | (Wire.read() << 8); // Odczyt danych osi X
    int16_t y = Wire.read() | (Wire.read() << 8); // Odczyt danych osi Y
    int16_t z = Wire.read() | (Wire.read() << 8); // Odczyt danych osi Z

    // Przeliczenie danych na przyspieszenie w jednostkach g
    float accelX = convertToAcceleration(x);
    float accelY = convertToAcceleration(y);
    float accelZ = convertToAcceleration(z);

    // Wyświetlenie odczytanych wartości przyspieszenia
    Serial.print(accelX);Serial.print(",");
    Serial.print(accelY);Serial.print(",");
    Serial.println(accelZ);
  }

  delay(100); // Odczyt co sekundę

}//end of void loop()


//------------------------
//    Sprawdza czy do mC jest podłaćzony LSM6DS3,
//    a dokladniej sprawdza czy rejestr 0x0f jest równy 0x69
//    return false or true
//------------------------
bool CheckConnectionLSM6DS3(){

  // Odczytaj rejestr 0x0f
  Wire.beginTransmission(LSM6DS3_ADDR);
  Wire.write(0x0F);  // Adres rejestru do odczytu
  Wire.endTransmission();
  
  // Poproś o odczyt danych
  Wire.requestFrom(LSM6DS3_ADDR, 1); // Odczytaj jednobajtowe dane
  if (Wire.available()) {
    byte data = Wire.read();
    if(data = 0x69) return true;
  }

  return false;

}//end of bool CheckConnectionLSM6DS3()





//----------------------------------
//    Przeliczenie danych rav na przyspieszenie ziemskie
//----------------------------------
float convertToAcceleration(int16_t rawValue) {
  // Wartość LSB na g dla zakresu ±2g (LSB/g)
  const float LSB_per_g = 0.00061; // Wartość dla tego zakresu pomiarowego

  // Przeliczenie wartości surowej na przyspieszenie w jednostkach g
  return rawValue * LSB_per_g;
}
