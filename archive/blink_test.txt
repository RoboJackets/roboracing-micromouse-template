/* #include <Arduino.h>

#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

struct Gyro {
  MPU6050 mpu;
  bool dmpReady = false;
  uint8_t devStatus = 0;
  uint16_t packetSize = 0;
  uint8_t fifoBuffer[64];

  float ypr[3] = {0, 0, 0};

  Quaternion q;
  VectorFloat gravity;

  elapsedMicros timer;

  void initializeGyro(){
    Wire.begin();
    Wire.setClock(400000);
    Wire.setTimeout(3000);

    mpu.initialize();
    devStatus = mpu.dmpInitialize();

    if (devStatus == 0) {
      mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      mpu.PrintActiveOffsets();

      mpu.setDMPEnabled(true);
      dmpReady = true;
      packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
      Serial.print("DMP Initialization failed (code ");
      Serial.print(devStatus);
      Serial.println(")");
    }
  }

  // returns true when new ypr was computed
  bool update(){
    if (!dmpReady) return false;
    //Serial.print("test1");

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      return true;
    }

    return false;
  }
};

//ch
//Gyro gyro{};

void setup() { 
  pinMode(36, OUTPUT); //formerly 22, 26 //programmable one
  pinMode(38, INPUT); //analog pin 38 (formerly A8)

  //ch
  Serial.begin(115200);
  //gyro.initializeGyro();
}

void loop() {

  digitalWrite(36, HIGH); //on //formerly 22, 26
  delayMicroseconds(300); //wait for 300 microseconds
  int val = analogRead(38); //Read analog pin 38 (formerly A8)
  Serial.println(val); //print print time yay
  digitalWrite(36, LOW); //off
  delay(100); //yolo lmao


  //delayMicroseconds(300);

  //light flash
  // digitalWrite(2, HIGH);
  // delay(100);
  // digitalWrite(22, LOW);
  //delay(100);

  // Serial.printf("Accel X: %d ", gyro.mpu.getAccelerationX());
  // Serial.print(" ");
  // Serial.printf("Accel Y: %d ",gyro.mpu.getAccelerationY());
  // Serial.print(" ");
  // Serial.printf("Accel Z: %d ", gyro.mpu.getAccelerationZ());
  // Serial.print(" ");

//Serial.printf("Test\n");
  //Serial.printf("accel: %d %d %d\n", gyro.mpu.getAccelerationX(), gyro.mpu.getAccelerationY(), gyro.mpu.getAccelerationZ());
  //ch 
// if (gyro.update()) {
//     Serial.printf("ypr: %f %f %f\n", gyro.ypr[0] * (180.0 / M_PI), gyro.ypr[1] * (180.0 / M_PI), gyro.ypr[2] * (180.0 / M_PI));
//   }

}

*/

#include <Arduino.h>
#include "MouseIO.h"
#include "TeensyIO.h"

#include "DRV8833.h"


//in1 36 in2 37
const int IN1_PIN = 36;
const int IN2_PIN = 37;
const int OUT1_PIN = 14;
const int OUT2_PIN = 15;

//const int testpin = 15;

DRV8833Motor motor(IN1_PIN, IN2_PIN, 1, 4); //in1, in2, offset, standby

// float readVolt(int pin) {
//   float reading = 0;
//   reading = analogRead(pin);
//   return reading / 1023.0 * 3.3;  // default 10-bit ADC -> volts
// }
// //print avg voltage reading of OUT1 and OUT2
// void report(const char* label) {
//   delay(50);  // let outputs settle
//   Serial.printf("%-16s OUT1 = %.2fV   OUT2 = %.2fV\n", label, readVolt(OUT1_PIN), readVolt(OUT2_PIN));
// }

// void setup() {
//   Serial.begin(115200);

//   pinMode(4, OUTPUT);
//   digitalWrite(4, HIGH); 
//   //standby is tied to 3.3V so the motor driver is always on, but pin 4 shld be connected to nothing
  

//   pinMode(OUT1_PIN, INPUT_PULLDOWN);  //ties the pin to ground so when nothing is driving it the voltage is 0
//   pinMode(OUT2_PIN, INPUT_PULLDOWN); //i guess we dont need it tho or smth idek

//   motor.begin();
// }

void setup( ) {
  motor.begin();
}

void loop() {
  // motor.drive(255);  
  // // report("fwd 100%");
  // motor.drive(128);  
  // // report("fwd 50%");
  // motor.drive(-255); 
  // // report("rev 100%");
  // motor.drive(-128); 
  // // report("rev 50%");
  // motor.drive(0);    
  // // report("coast");
  // motor.brake();     
  // // report("brake");
  // //Serial.println("---");
  // delay(2000);

  // motor.drive(100);    //forward ~40% power
  // delay(2000);

  // motor.brake();       //stop fast
  // delay(1000);

  // motor.drive(-100);   //reverse
  // delay(2000);

  // motor.drive(0);      //coast
  // delay(1000);

  for(int i = 0; i < 255; i+=1) {
    motor.drive(i);  //gradually increase speed
    delay(100);
    Serial.printf("%d %n", i);
    if(i == 250) {
      delay(1000);
      i = 0;
    }
  }

  
  //Serial.printf("Test pin voltage: %.2fV\n", readVolt(testpin));
}