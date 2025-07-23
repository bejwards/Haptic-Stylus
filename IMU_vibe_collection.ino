#include <Wire.h>

#define Accel_X_Upper 0x1f
#define Accel_X_Lower 0x20
#define Accel_Y_Upper 0x21
#define Accel_Y_Lower 0x22
#define Accel_Z_Upper 0x23
#define Accel_Z_Lower 0x24

#define Gyro_X_Upper 0x25
#define Gyro_X_Lower 0x26
#define Gyro_Y_Upper 0x27
#define Gyro_Y_Lower 0x28
#define Gyro_Z_Upper 0x29
#define Gyro_Z_Lower 0x2a

#define accel_const 0.0004882887
#define gyro_const 0.06103608759

#define Config 0x03

byte IMU_Address = B1101000;

int fsrPin = A3; //FSR connected to analog pin 3
int fsr = 0;  // variable to store the value read from fsr

byte axu;   //accelerometer x axis upper byte
byte axl;   //accelerometer x axis lower byte
byte ayu;   //y axis
byte ayl;
byte azu;
byte azl;
byte gxu;   //gyro
byte gxl;
byte gyu;
byte gyl;
byte gzu;
byte gzl;

float axtot = 0, aytot = 0, aztot = 0, gxtot = 0, gytot = 0, gztot = 0;               //current total values
float mfsr = 0,maxtot = 0, maytot = 0, maztot = 0, mgxtot = 0, mgytot = 0, mgztot = 0;         //maximum total values

void ReadFromIMU(registerAddress);

void setup() {

  Wire.beginTransmission(IMU_Address);
  Wire.write(78);                         //register for powering on acceleromoter and gyro
  Wire.write(15);                         //dec number corresponding to bit sequence for accel & gyro on
  Wire.endTransmission();
  delayMicroseconds(200);                 //delay required after updating power management register

  Wire.beginTransmission(IMU_Address);
  Wire.write(19);                         //register for setting slew rate
  Wire.write(45);                         //dec number corresponding to bit sequence for slew rate <2ns
  Wire.endTransmission();

  /*Wire.beginTransmission(IMU_Address);
  Wire.write(19);                         //register for setting slew rate
  Wire.write(19);                         //register for setting slew rate
  Wire.endTransmission();*/


  Wire.setClock(1000000);
  
  Serial.begin(2000000);

}



void loop() {

  Wire.beginTransmission(IMU_Address);
  Wire.write(Accel_X_Upper);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  axu = Wire.read();
  
  Wire.beginTransmission(IMU_Address);
  Wire.write(Accel_X_Lower);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  axl = Wire.read();

  Wire.beginTransmission(IMU_Address);
  Wire.write(Accel_Y_Upper);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  ayu = Wire.read();
  
  Wire.beginTransmission(IMU_Address);
  Wire.write(Accel_Y_Lower);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  ayl = Wire.read();
  
  Wire.beginTransmission(IMU_Address);
  Wire.write(Accel_Z_Upper);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  azu = Wire.read();
  
  Wire.beginTransmission(IMU_Address);
  Wire.write(Accel_Z_Lower);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  azl = Wire.read();  

  Wire.beginTransmission(IMU_Address);
  Wire.write(Gyro_X_Upper);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  gxu = Wire.read();
  
  Wire.beginTransmission(IMU_Address);
  Wire.write(Gyro_X_Lower);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  gxl = Wire.read();

  Wire.beginTransmission(IMU_Address);
  Wire.write(Gyro_Y_Upper);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  gyu = Wire.read();
  
  Wire.beginTransmission(IMU_Address);
  Wire.write(Gyro_Y_Lower);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  gyl = Wire.read();
  
  Wire.beginTransmission(IMU_Address);
  Wire.write(Gyro_Z_Upper);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  gzu = Wire.read();
  
  Wire.beginTransmission(IMU_Address);
  Wire.write(Gyro_Z_Lower);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  gzl = Wire.read();

  /*axtot = ((axu<<8)+axl)*accel_const, aytot = ((ayu<<8)+ayl)*accel_const, aztot = ((azu<<8)+azl)*accel_const;
  gxtot = ((gxu<<8)+gxl)*gyro_const, gytot = ((gyu<<8)+gyl)*gyro_const, gztot = ((gzu<<8)+gzl)*gyro_const;

  if (axtot>maxtot){
    maxtot=axtot;
  }
  if (aytot>maytot){
    maytot=aytot;
  }
  if (aztot>maztot){
    maztot=aztot;
  }
  if (gxtot>mgxtot){
    mgxtot=gxtot;
  }
  if (gytot>mgytot){
    mgytot=gytot;
  }
  if (gztot>mgztot){
    mgztot=gztot;
  }*/
  
  
  fsr = analogRead(fsrPin);  // read the input pin

  Serial.print(fsr);
  Serial.print(",");
  Serial.print(axu);
  Serial.print(",");
  Serial.print(axl);
  Serial.print(",");
  Serial.print(ayu);
  Serial.print(",");
  Serial.print(ayl);
  Serial.print(",");
  Serial.print(azu);
  Serial.print(",");
  Serial.print(azl);
  Serial.print(",");
  Serial.print(gxu);
  Serial.print(",");
  Serial.print(gxl);
  Serial.print(",");
  Serial.print(gyu);
  Serial.print(",");
  Serial.print(gyl);
  Serial.print(",");
  Serial.print(gzu);
  Serial.print(",");
  Serial.println(gzl);

 /*Serial.print(fsr);
  Serial.print("  ");
  Serial.print(axtot, 5); 
  Serial.print("  ");
  Serial.print(aytot, 5);
  Serial.print("  ");
  Serial.print(aztot, 5); 
  Serial.print("  ");
  Serial.print(gxtot, 5);
  Serial.print("  ");
  Serial.print(gytot, 5);
  Serial.print("  ");
  Serial.print(gztot, 5);
  Serial.print("       maxtot:");
  Serial.print(maxtot, 5); 
  Serial.print("  maytot:");
  Serial.print(maytot, 5);
  Serial.print("  maztot:");
  Serial.print(maztot, 5); 
  Serial.print("  mgxtot:");
  Serial.print(mgxtot, 5);
  Serial.print("  mgytot:");
  Serial.print(mgytot, 5);
  Serial.print("  mgztot:");
  Serial.println(mgztot, 5);
*/
}

void ReadFromIMU(registerAddress){
  Wire.beginTransmission(IMU_Address);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(IMU_Address, 1);
  axu = Wire.read();
  }
