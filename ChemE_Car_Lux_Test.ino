#include <LTR390.h>
#include <Wire.h>

#define I2C_ADDRESS 0x53

LTR390 ltr390(I2C_ADDRESS);

const float LUX_THRESHOLD = 1;
const int LED = 10;
bool on = true;
unsigned long start = 0;
unsigned long end = 0;
unsigned long countdown = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  delay(1000);
  Wire.begin();
  if(!ltr390.init()){
    Serial.println("LTR390 not connected!");
  }

  ltr390.setMode(LTR390_MODE_ALS);
  ltr390.setGain(LTR390_GAIN_18);
  
  // highest possible resolution to make sure we stop the cart
  // as close to the instant of the reaction running it's course
  // as possible. If this causes an unacceptable slowdown in the 
  // operation of the LTR, feel free to change back to default 
  // value of 18-bit
  ltr390.setResolution(LTR390_RESOLUTION_18BIT);

  // SSR's initial state should be off (governed by ssr_flag). 
  // SSR being off means that power can flow from battery to motor
  // and motor is on.
  digitalWrite(LED, HIGH);
  Serial.println("Three");
  delay(1000);
  Serial.println("Two");
  delay(1000);
  Serial.println("One");
  delay(1000);
  Serial.println("Go!");
  delay(1000);
  start = micros();
}

void loop() {
  if (on) {
    double val = ltr390.getLux();
    Serial.println(val);
    if (val < LUX_THRESHOLD){
      end = micros();
      on = false;
      Serial.println("Done!");
      Serial.print("Time: ");
      Serial.print((end - start) / 1000000.0);
      Serial.println(" seconds");
    }
  }

}
