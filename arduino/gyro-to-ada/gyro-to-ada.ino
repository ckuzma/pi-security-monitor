#include<Wire.h>

// ITG/MPU Sensor Stuff
const int MPU_addr=0x68;  // I2C address for ITG-MTU
int ax, ay, az, temp, gx, gy, gz;

void setup(){
 Serial.begin(9600);
 setupGyro();
}

void setupGyro() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  // Get readings from MPU
  updateGyroReadings();

  // Print values in a String format
  Serial.println(
    " ax:" + String(ax) +
    " ay:" + String(ay) +
    " az:" + String(az) +
    " gx:" + String(gx) +
    " gy:" + String(gy) +
    " gz:" + String(gz) +
    " temp:" + String(temp)
    );

  // Delay
  delay(100);
}

void updateGyroReadings() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  ax = Wire.read()<<8|Wire.read();
  ay = Wire.read()<<8|Wire.read();
  az = Wire.read()<<8|Wire.read();
  temp = Wire.read()<<8|Wire.read();
  gx = Wire.read()<<8|Wire.read();
  gy = Wire.read()<<8|Wire.read();
  gz = Wire.read()<<8|Wire.read();
}