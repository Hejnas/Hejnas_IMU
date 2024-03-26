//****************************************************************
//
//              ...:::  Hejnas IMU   :::...
//
//****************************************************************

#include <Wire.h>
#include "HejnasLibaryLSM6DS3/HejnasLibaryLSM6DS3.h"

#define LSM6DS3_ADDR 0x6B


String version = "v1.0";

//-------------------------
//    setup
//-------------------------
void setup() {

  //wywałeanie biblioteki
  //HejnasLibaryLSM6DS3 LSM6DS3;

  //Procedura początkowa
  Wire.begin();
  Serial.begin(57600);
  delay(1000);
  Serial.print("\nHejnas IMU ");
  Serial.println(version);

  //Sprawdzenie czy na i2c jest podłączony LSM6DS3
  byte connectionStatus = CheckConnectionLSM6DS3();
  if (connectionStatus = true)Serial.println("LSM6DS3 connection OK");
  else {
    Serial.println("LSM6DS3 connection nOK");
    while (1);
  }

  // Konfiguracja akcelerometru
  Wire.beginTransmission(LSM6DS3_ADDR); // Rozpoczęcie transmisji do akcelerometru
  Wire.write(0x10);                     // Rejestr kontrolny dla konfiguracji
  Wire.write(LSM6DS3_RATE_104_HZ << 4 + LSM6DS3_ACCEL_RANGE_16_G << 2);
  Wire.endTransmission();               // Zakończenie transmisji

  // Konfiguracja gyroskopu
  Wire.beginTransmission(LSM6DS3_ADDR); // Rozpoczęcie transmisji do akcelerometru
  Wire.write(0x11);                     // Rejestr kontrolny dla konfiguracji
  Wire.write(0b01001100);   ///LSM6DS3_RATE_104_HZ << 4 + LSM6DS3_GYRO_RANGE_2000_DPS << 2);
  Wire.endTransmission();               // Zakończenie transmisji

  Serial.println("acclX,acclY,acclZ,gyroX,gyroY,gyroZ");

}//end of void setup()


int16_t acclRawX;
int16_t acclRawY;
int16_t acclRawZ;
int16_t gyroRawX;
int16_t gyroRawY;
int16_t gyroRawZ;
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
    acclRawX = Wire.read() | (Wire.read() << 8); // Odczyt danych osi X
    acclRawY = Wire.read() | (Wire.read() << 8); // Odczyt danych osi Y
    acclRawZ = Wire.read() | (Wire.read() << 8); // Odczyt danych osi Z
  }

  // Odczyt danych z żyroskopu
  Wire.beginTransmission(LSM6DS3_ADDR);  // Rozpoczęcie transmisji do żyroskopu
  Wire.write(0x22);                      // Rejestr danych X żyroskopu (LSB)
  Wire.endTransmission(false);            // Zakończenie transmisji (false - bez stop bitu)

  Wire.requestFrom(LSM6DS3_ADDR, 6);     // Odczyt 6 bajtów danych (po 2 bajty na oś)
  if (Wire.available() >= 6) {
    gyroRawX = Wire.read() | (Wire.read() << 8); // Odczyt danych osi X
    gyroRawY = Wire.read() | (Wire.read() << 8); // Odczyt danych osi Y
    gyroRawZ = Wire.read() | (Wire.read() << 8); // Odczyt danych osi Z
  }

  // Przeliczenie danych na przyspieszenie w jednostkach g
  float accelX = convertToAcceleration(acclRawX);
  float accelY = convertToAcceleration(acclRawY);
  float accelZ = convertToAcceleration(acclRawZ);

  // Przeliczenie danych na prędkość kątową w jednostkach DPS
  float gyroX = convertToDPS(gyroRawX);
  float gyroY = convertToDPS(gyroRawY);
  float gyroZ = convertToDPS(gyroRawZ);

  // Wyświetlenie odczytanych wartości
  Serial.print(accelX); Serial.print(",");
  Serial.print(accelY); Serial.print(",");
  Serial.print(accelZ); Serial.print(",");
  Serial.print(gyroX); Serial.print(",");
  Serial.print(gyroY); Serial.print(",");
  Serial.println(gyroZ);


  delay(10); // Odczyt co sekundę

}//end of void loop()


//------------------------
//    Sprawdza czy do mC jest podłaćzony LSM6DS3,
//    a dokladniej sprawdza czy rejestr 0x0f jest równy 0x69
//    return false or true
//------------------------
bool CheckConnectionLSM6DS3() {

  // Odczytaj rejestr 0x0f
  Wire.beginTransmission(LSM6DS3_ADDR);
  Wire.write(LSM6DS3_WHO_AM_I);  // Adres rejestru do odczytu
  Wire.endTransmission();

  // Poproś o odczyt danych
  Wire.requestFrom(LSM6DS3_ADDR, 1); // Odczytaj jednobajtowe dane
  if (Wire.available()) {
    byte data = Wire.read();
    if (data = LSM6DS3_ID) return true;
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




float convertToDPS(int16_t raw) {
  // Zakres przetwornika ADC żyroskopu (16-bit)
  const float gyroRange = 125.0; // Zakres żyroskopu w DPS (stopni na sekundę)

  // Wartość skali dla danego zakresu w jednostkach na bit (DPS/bit)
  const float scale = gyroRange / 32768.0; // 32768 = 2^15 (zakres 16-bitów)

  // Przeliczenie surowych danych na prędkość kątową w jednostkach DPS
  return raw * scale;
}
