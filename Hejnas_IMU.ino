//****************************************************************
//
//              ...:::  Hejnas IMU   :::...
//
//****************************************************************

#include <Wire.h>

byte LSM6DS3_ADDRESS = 0x6B;
String version = "v1.0";

//-------------------------
//    setup
//-------------------------
void setup() {
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
  
  
}//end of void setup()



//------------------------
//    loop
//------------------------
void loop() {
  

}//end of void loop()


//------------------------
//    Sprawdza czy do mC jest podłaćzony LSM6DS3,
//    a dokladniej sprawdza czy rejestr 0x0f jest równy 0x69
//    return false or true
//------------------------
bool CheckConnectionLSM6DS3(){

  // Odczytaj rejestr 0x0f
  Wire.beginTransmission(LSM6DS3_ADDRESS);
  Wire.write(0x0F);  // Adres rejestru do odczytu
  Wire.endTransmission();
  
  // Poproś o odczyt danych
  Wire.requestFrom(LSM6DS3_ADDRESS, 1); // Odczytaj jednobajtowe dane
  if (Wire.available()) {
    byte data = Wire.read();
    if(data = 0x69) return true;
  }

  return false;

}//end of bool CheckConnectionLSM6DS3()
