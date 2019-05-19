#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>

GridEYE grideye;

void setup() {

  // Start your preferred I2C object 
  Wire.begin();
  // Library assumes "Wire" for I2C but you can pass something else with begin() if you like
  grideye.begin();
  // Pour a bowl of serial
  Serial.begin(115200);

}

void loop() {

  // variables to store temperature values
  float testPixelValue = 0;
  float hotPixelValue = 0;
  int hotPixelIndex = 0;

  // for each of the 64 pixels, record the temperature and compare it to the 
  // hottest pixel that we've tested. If it's hotter, that becomes the new
  // king of the hill and its index is recorded. At the end of the loop, we 
  // should have the index and temperature of the hottest pixel in the frame
  for(unsigned char i = 0; i < 64; i++){
    testPixelValue = (grideye.getPixelTemperature(i) - grideye.getDeviceTemperature());
      if(testPixelValue > hotPixelValue){
        hotPixelValue = testPixelValue;
        hotPixelIndex = i;
      }
  }

  // Print the result in human readable format
  Serial.print("The hottest pixel is #");
  Serial.print(hotPixelIndex);
  Serial.print("temp.");
  Serial.print(hotPixelValue);
  Serial.println("C");

  // toss in a delay because we don't need to run all out
  delay(70);

}
