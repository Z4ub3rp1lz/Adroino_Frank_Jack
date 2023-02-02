
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <Wire.h>
RH_ASK driver(2000, 9, 2, 10); // ESP8266 or ESP32: do not use pin 11
const int MPUADD = 0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int pulsered,pulseblue,pulsegreen;
char msg[]  = "00110000";

void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
  Wire.begin();
  Wire.beginTransmission(MPUADD);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
}

void loop()
{
 driver.send((uint8_t *)msg, strlen(msg));
 driver.waitPacketSent();
  Wire.beginTransmission(MPUADD);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPUADD,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  pulsered = (AcX/100)*255;                  // calculate Pluselengh of red  
  pulseblue = (AcY/100)*255;                 // calculate Pluselengh of blue
  pulsegreen = (AcZ/100)*255;                // calculate Pulselengh of green
  digitalWrite(7,HIGH);
  delayMicroseconds(pulsered);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);             
  delayMicroseconds(pulsegreen);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);             
  delayMicroseconds(pulseblue);
  digitalWrite(9,LOW);
 Serial.println(msg);
 String str =  "AcX: " + String(AcX);
 str.toCharArray(msg,str.length());
 driver.send((uint8_t *)msg, strlen(msg));
 driver.waitPacketSent();
 str = "AcY: " +String(AcY);
 str.toCharArray(msg,str.length());
 driver.send((uint8_t *)msg, strlen(msg));
 driver.waitPacketSent();
 str  ="AcZ: " +String(AcZ);
 str.toCharArray(msg,str.length());
 driver.send((uint8_t *)msg, strlen(msg));
 driver.waitPacketSent();
 str  ="Tmp: " +String(Tmp);
 str.toCharArray(msg,str.length());
 driver.send((uint8_t *)msg, strlen(msg));
 driver.waitPacketSent();
 str  ="GyX: " +String(GyX);
 str.toCharArray(msg,str.length());
 driver.send((uint8_t *)msg, strlen(msg));
 driver.waitPacketSent();
 str ="GyY: " +String(GyY);
 str.toCharArray(msg,str.length());
 driver.send((uint8_t *)msg, strlen(msg));
 driver.waitPacketSent();
 str ="GyZ: " +String(GyZ);
 str.toCharArray(msg,str.length());
 driver.send((uint8_t *)msg, strlen(msg));
 driver.waitPacketSent();
}
